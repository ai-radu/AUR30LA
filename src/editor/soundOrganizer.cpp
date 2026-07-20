#include <iostream>
#include "aur.hpp"

static c1 soPopup = false;
const c8* chunk_id       = "RIFF";
const c8* chunk_size     = "----"; // 4 bytes
const c8* format         = "WAVE";
const c8* subchunk1_id   = "fmt ";
const c8* subchunk2_id   = "data";
const c8* subchunk2_size = "----"; // 4 bytes
const c32 subchunk1_size   = 16;
const c32 audio_format     = 1;
const c32 num_channels     = 2;
const c32 bits_per_sample  = 16;
const c32 block_align      = num_channels * (bits_per_sample / 8);
const c8* waves[] = { "Sine", "Square", "Saw", "Triangle", "Noise" };
static const c32 sampleRateValues[] = {
    8000, 11025, 16000, 22050, 24000, 32000, 44100,
    48000, 88200, 96000, 176400, 192000, 352800, 384000
};
static const c8* sampleRate[] = {
    "8000", "11025", "16000", "22050", "24000", "32000", "44100",
    "48000", "88200", "96000", "176400", "192000", "352800", "384000"
};
int sampleRateIndex = 6;
int sample_rate = sampleRateValues[6];
struct Operator {
    c32 wave         = 0;
    f32 frequency    = 440.0f;
    f32 vibratoFreq  = 5.0f;
    f32 vibratoDepth = 5.0f;
    f32 modulation   = 0.0f;
};
struct Clip {
    f32 scroll        = 0.0f;
    f32 speed         = 0.005;
    c32 points        = 512;
    f32 view          = 0.025f;
    
    f32 volume        = 0.3f;
    f32 duration      = 2.0f;
    
    f32 attack        = 0.01f;
    f32 decay         = 0.1f;
    f32 sustain       = 0.8f;
    f32 release       = 0.2f;
    f32 noise         = 0.0f;
    
    f32 reverbMix     = 0.3f;
    f32 reverbDecay   = 0.3f;
    f32 chorusDepth   = 0.2f;
    f32 chorusRate    = 0.8f;

    c32 wave1         = 0;
    f32 frequency1    = 110.0f;
    f32 vibratoFreq1  = 1.0f;
    f32 vibratoDepth1 = 1.0f;
    
    f32 modulation1   = 1.2f;
    
    c32 wave2         = 0;
    f32 frequency2    = 220.0f;
    f32 vibratoFreq2  = 2.22f;
    f32 vibratoDepth2 = 2.22f;
    
    f32 modulation2   = 2.4f;
    
    c32 wave3         = 0;
    f32 frequency3    = 330.0f;
    f32 vibratoFreq3  = 3.33f;
    f32 vibratoDepth3 = 3.33f;
    
    f32 modulation3   = 3.6f;
    
    c32 wave4         = 0;
    f32 frequency4    = 440.0f;
    f32 vibratoFreq4  = 4.44f;
    f32 vibratoDepth4 = 4.44f;
    
    f32 modulation4   = 2.4f;
    
    c32 wave5         = 0;
    f32 frequency5    = 550.0f;
    f32 vibratoFreq5  = 5.55f;
    f32 vibratoDepth5 = 5.55f;
    
    f32 modulation5   = 1.2f;
    
    c32 wave6         = 0;
    f32 frequency6    = 660.0f;
    f32 vibratoFreq6  = 6.66f;
    f32 vibratoDepth6 = 6.66f;
    
    f32 modulation6   = 2.4f;
    
    c32 wave7         = 0;
    f32 frequency7    = 770.0f;
    f32 vibratoFreq7  = 7.77f;
    f32 vibratoDepth7 = 7.77f;
    
    f32 modulation7   = 3.6f;
    
    c32 wave8         = 0;
    f32 frequency8    = 880.0f;
    f32 vibratoFreq8  = 8.88f;
    f32 vibratoDepth8 = 8.88f;
};
struct stereo {
    s16 left;
    s16 right;
};
ma_engine engine;
ma_sound sound;
ma_sound previewSound;
ma_audio_buffer previewBuffer;
std::vector<Clip> clips;
c8 name[64] = "test";
c8 path[64] = "../assets/audio/soundOrganizer/";
f32 noteToFreq(c32 note) { return 440.0f * std::powf(2.0f, (note - 69) / 12.0f); }
// FIXME
float getNoise() {
    static u32 seed = 123456789;
    seed = seed * 1664525u + 1013904223u;
    return ((seed & 0xFFFF) / 32768.0f) * 2.0f - 1.0f;
}
float oscillator(c32 type, f32 phase) {
    switch (type) {
        case 0: return std::sin(2 * PI * phase); // sine
        case 1: return std::sin(2 * PI * phase) >= 0 ? 1.0f : -1.0f; // square
        case 2: return 2.0f * (phase - std::floor(phase + 0.5f)); // saw
        case 3: return 2.0f * std::fabs(2 * (phase - std::floor(phase + 0.5f))) - 1.0f; // triangle
        case 4: return getNoise(); // noise
        default: return 0.0f;
    }
}
float getEnvelope(const Clip& clip, f32 t) {
    f32 attack  = std::max(clip.attack,  0.0001f);
    f32 decay   = std::max(clip.decay,   0.0001f);
    f32 release = std::max(clip.release, 0.0001f);
    if (t < attack)         return t / attack;
    if (t < attack + decay) return 1.0f + (t - attack) / decay * (clip.sustain - 1.0f);
    if (t < clip.duration - release) return clip.sustain;
    f32 st = (t - (clip.duration - release)) / release;
    return clip.sustain * (1.0f - st);
}
float synth(const Clip& c, f32 t) {
    f32 op1 = oscillator(c.wave1, c.frequency1 * t + c.vibratoDepth1 * std::sin(2 * PI * c.vibratoFreq1 * t));
    f32 op2 = oscillator(c.wave2, c.frequency2 * t + c.vibratoDepth2 * std::sin(2 * PI * c.vibratoFreq2 * t));
    f32 op3 = oscillator(c.wave3, c.frequency3 * t + c.vibratoDepth3 * std::sin(2 * PI * c.vibratoFreq3 * t));
    f32 op4 = oscillator(c.wave4, c.frequency4 * t + c.vibratoDepth4 * std::sin(2 * PI * c.vibratoFreq4 * t));
    f32 op5 = oscillator(c.wave5, c.frequency5 * t + c.vibratoDepth5 * std::sin(2 * PI * c.vibratoFreq5 * t));
    f32 op6 = oscillator(c.wave6, c.frequency6 * t + c.vibratoDepth6 * std::sin(2 * PI * c.vibratoFreq6 * t));
    f32 op7 = oscillator(c.wave7, c.frequency7 * t + c.vibratoDepth7 * std::sin(2 * PI * c.vibratoFreq7 * t));
    f32 op8 = oscillator(c.wave8, c.frequency8 * t + c.vibratoDepth8 * std::sin(2 * PI * c.vibratoFreq8 * t));
    f32 gain = 1.0f +
        fabs(c.modulation1) +
        fabs(c.modulation2) +
        fabs(c.modulation3) +
        fabs(c.modulation4) +
        fabs(c.modulation5) +
        fabs(c.modulation6) +
        fabs(c.modulation7);
    return (
        op1 + c.modulation1 *
        op2 + c.modulation2 *
        op3 + c.modulation3 *
        op4 + c.modulation4 *
        op5 + c.modulation5 *
        op6 + c.modulation6 *
        op7 + c.modulation7 * op8
    ) / gain;
}
stereo generate(const Clip& c, f32 t) {
    f32 sample = synth(c, t);
    f32 wet = sample;
    // FIXME chorus
    f32 chorus = 0.0f;
    if (c.chorusDepth > 0.001f) {
        f32 lfo1 = std::sin(2 * PI * c.chorusRate * t);
        f32 lfo2 = std::sin(2 * PI * c.chorusRate * 1.3f * t + 2.0f);
        f32 m1 = 0.0025f + c.chorusDepth * 0.007f * lfo1;
        f32 m2 = 0.003f  + c.chorusDepth * 0.007f * lfo2;
        f32 chorus1 = (t > m1) ? synth(c, t - m1) : sample;
        f32 chorus2 = (t > m2) ? synth(c, t - m2) : sample;
        wet += (chorus1 + chorus2) * 0.35f * c.chorusDepth;
    }
    // reverb
    if (c.reverbMix > 0.001f) {
        f32 fb = 0.6f + c.reverbDecay * 0.35f;
        f32 r1 = (t > 0.035f) ? synth(c, t - 0.037f) * fb : 0.0f;
        f32 r2 = (t > 0.059f) ? synth(c, t - 0.059f) * fb * 0.85f : 0.0f;
        f32 r3 = (t > 0.091f) ? synth(c, t - 0.091f) * fb * 0.7f  : 0.0f;
        f32 r4 = (t > 0.131f) ? synth(c, t - 0.131f) * fb * 0.55f : 0.0f;
        wet += (r1 + r2 + r3 + r4) * c.reverbMix * 1.5f;
    }
    f32 noise = getNoise() * c.noise;
    f32 envelope = getEnvelope(c, t);
    f32 final = (wet + noise) * envelope * c.volume;
    final = std::clamp(final, -1.0f, 1.0f);
    s16 value = (s16)(final * 32767.0f);
    return {value, value};
}
void initAudio() {
    ma_engine_config config = ma_engine_config_init();
    ma_engine_init(&config, &engine);
}
void uninitAudio() {
    ma_sound_uninit(&sound);
    ma_sound_uninit(&previewSound);
    ma_audio_buffer_uninit(&previewBuffer);
    ma_engine_uninit(&engine);
};
void saveWav() {
    std::string savePath = std::string(path) + name + ".wav";
    std::ofstream file(savePath, std::ios::binary);
    if (!file.is_open()) { tellme("[WARNING] soundOrganizer.cpp > saveWav() ? !file.is_open()"); return; }
    uint32_t totalSamples = 0;
    for (const auto& clip : clips) { totalSamples += static_cast<u32>(sample_rate * clip.duration); }
    uint16_t wavaudioformat = audio_format;
    uint16_t wavnumchannels = num_channels;
    uint16_t wavblockalign  = block_align;
    uint16_t wavbitspersample = bits_per_sample;
    
    uint32_t wavsamplerate  = sample_rate;
    uint32_t subchunk2_size = totalSamples * num_channels * (bits_per_sample / 8);
    uint32_t chunkSize      = 36 + subchunk2_size;
    uint32_t byteRate       = sample_rate  * num_channels * (bits_per_sample / 8);
    file.write(chunk_id,                                     4);
    file.write(reinterpret_cast<c8*>(&chunkSize),            4);
    file.write(format,                                       4);
    file.write(subchunk1_id,                                 4);
    file.write(reinterpret_cast<const c8*>(&subchunk1_size), 4);
    file.write(reinterpret_cast<c8*>(&wavaudioformat),       2);
    file.write(reinterpret_cast<c8*>(&wavnumchannels),       2);
    file.write(reinterpret_cast<c8*>(&wavsamplerate),        4);
    file.write(reinterpret_cast<c8*>(&byteRate),             4);
    file.write(reinterpret_cast<c8*>(&wavblockalign),        2);
    file.write(reinterpret_cast<c8*>(&wavbitspersample),     2);
    file.write(subchunk2_id,                                 4);
    file.write(reinterpret_cast<c8*>(&subchunk2_size),       4);
    for (const auto& clip : clips) {
        c32 samples = (c32)(sample_rate * clip.duration);
        for (c32 i = 0; i < samples; i++) {
            f32 t  = (f32)i / sample_rate;
            stereo s = generate(clip, t);
            file.write(reinterpret_cast<c8*>(&s.left),  2);
            file.write(reinterpret_cast<c8*>(&s.right), 2);
        };
    };
}
void playPreview(c32 index) {
    if (index >= clips.size()) { tellme("[WARNING] playPreview() ? clipIndex >= clips.size()"); return; };
    const Clip& clip = clips[index];
    c32 sampleRateEngine = ma_engine_get_sample_rate(&engine);
    c32 total = (c32)(sampleRateEngine * clip.duration);
    static std::vector<int16_t> pcm;
    pcm.resize(total * 2);
    for (c32 i = 0; i < total; i++) {
        f32 t  = (f32)i / sampleRateEngine;
        stereo s = generate(clip, t);
        pcm[i * 2]     = s.left;
        pcm[i * 2 + 1] = s.right;
    };
    ma_audio_buffer_config config = ma_audio_buffer_config_init(ma_format_s16, 2, total, pcm.data(), nullptr);
    static c1 previewBufferInit = false;
    if (previewBufferInit) ma_audio_buffer_uninit(&previewBuffer);
    ma_audio_buffer_init(&config, &previewBuffer);
    previewBufferInit = true;
    
    ma_sound_stop(&previewSound);
    static c1 previewSoundInit = false;
    if (previewSoundInit) ma_sound_uninit(&previewSound);
    previewSoundInit = true;
    ma_sound_init_from_data_source(&engine, &previewBuffer, MA_SOUND_FLAG_DECODE, nullptr, &previewSound);
    ma_sound_start(&previewSound);
}
void playWav() {
    std::string entire = std::string(path) + name + ".wav";
    ma_sound_uninit(&sound);
    if(ma_sound_init_from_file(&engine, entire.c_str(), 0, nullptr, nullptr, &sound) != MA_SUCCESS) {
        tellme("[WARNING] soundOrganizer.cpp > playWav() ? !ma_sound_init_from_file");
        return;
    }
    ma_sound_start(&sound);
}
void addNote () {
    Clip c;
    c.duration;
    c.volume;

    c.attack;
    c.decay;
    c.sustain;
    c.release;
    c.noise;

    c.reverbMix;
    c.reverbDecay;
    c.chorusDepth;
    c.chorusRate;
    
    c.wave1;
    c.frequency1;
    c.vibratoFreq1;
    c.vibratoDepth1;

    c.modulation1;

    c.wave2;
    c.frequency2;
    c.vibratoFreq2;
    c.vibratoDepth2;

    c.modulation2;

    c.frequency3;
    c.vibratoFreq3;
    c.vibratoDepth3;

    c.modulation3;

    c.frequency4;
    c.vibratoFreq4;
    c.vibratoDepth4;

    c.modulation4;

    c.frequency5;
    c.vibratoFreq5;
    c.vibratoDepth5;

    c.modulation5;

    c.frequency6;
    c.vibratoFreq6;
    c.vibratoDepth6;

    c.modulation6;

    c.frequency7;
    c.vibratoFreq7;
    c.vibratoDepth7;

    c.modulation7;

    c.frequency8;
    c.vibratoFreq8;
    c.vibratoDepth8;

    clips.emplace_back(c);
}
void deleteNote(c32 i) { clips.erase(clips.begin() + i); }
void randomize(Clip& c) { // FIXME ?
    c.reverbMix     = 0.0f  + (f32)std::rand() / RAND_MAX * (1.0f    -  0.0f);
    c.reverbDecay   = 0.0f  + (f32)std::rand() / RAND_MAX * (1.0f    -  0.0f);
    c.chorusDepth   = 0.0f  + (f32)std::rand() / RAND_MAX * (0.3f    -  0.0f);
    c.chorusRate    = 0.0f  + (f32)std::rand() / RAND_MAX * (4.0f    -  0.0f);
    
    c.wave1         = std::rand() % (IM_COUNTOF(waves) - 2);
    c.frequency1    = 20.0f + (f32)std::rand() / RAND_MAX * (2000.0f - 20.0f);
    c.vibratoFreq1  = 0.0f  + (f32)std::rand() / RAND_MAX * (100.0f  -  0.0f);
    c.vibratoDepth1 = 0.0f  + (f32)std::rand() / RAND_MAX * (20.0f   -  0.0f);
    
    c.modulation1   = 0.0f  + (f32)std::rand() / RAND_MAX * (10.0f   -  0.0f);
    
    c.wave2         = std::rand() % (IM_COUNTOF(waves) - 2);
    c.frequency2    = 20.0f + (f32)std::rand() / RAND_MAX * (2000.0f - 20.0f);
    c.vibratoFreq2  = 0.0f  + (f32)std::rand() / RAND_MAX * (100.0f  -  0.0f);
    c.vibratoDepth2 = 0.0f  + (f32)std::rand() / RAND_MAX * (20.0f   -  0.0f);
    
    c.modulation2   = 0.0f  + (f32)std::rand() / RAND_MAX * (10.0f   -  0.0f);
    
    c.wave3         = std::rand() % (IM_COUNTOF(waves) - 2);
    c.frequency3    = 20.0f + (f32)std::rand() / RAND_MAX * (2000.0f - 20.0f);
    c.vibratoFreq3  = 0.0f  + (f32)std::rand() / RAND_MAX * (100.0f  -  0.0f);
    c.vibratoDepth3 = 0.0f  + (f32)std::rand() / RAND_MAX * (20.0f   -  0.0f);
    
    c.modulation3   = 0.0f  + (f32)std::rand() / RAND_MAX * (10.0f   -  0.0f);
    
    c.wave4         = std::rand() % (IM_COUNTOF(waves) - 2);
    c.frequency4    = 20.0f + (f32)std::rand() / RAND_MAX * (2000.0f - 20.0f);
    c.vibratoFreq4  = 0.0f  + (f32)std::rand() / RAND_MAX * (100.0f  -  0.0f);
    c.vibratoDepth4 = 0.0f  + (f32)std::rand() / RAND_MAX * (20.0f   -  0.0f);
    
    c.modulation4   = 0.0f  + (f32)std::rand() / RAND_MAX * (10.0f   -  0.0f);
    
    c.wave5         = std::rand() % (IM_COUNTOF(waves) - 2);
    c.frequency5    = 20.0f + (f32)std::rand() / RAND_MAX * (2000.0f - 20.0f);
    c.vibratoFreq5  = 0.0f  + (f32)std::rand() / RAND_MAX * (100.0f  -  0.0f);
    c.vibratoDepth5 = 0.0f  + (f32)std::rand() / RAND_MAX * (20.0f   -  0.0f);
    
    c.modulation5   = 0.0f  + (f32)std::rand() / RAND_MAX * (10.0f   -  0.0f);
    
    c.wave6         = std::rand() % (IM_COUNTOF(waves) - 2);
    c.frequency6    = 20.0f + (f32)std::rand() / RAND_MAX * (2000.0f - 20.0f);
    c.vibratoFreq6  = 0.0f  + (f32)std::rand() / RAND_MAX * (100.0f  -  0.0f);
    c.vibratoDepth6 = 0.0f  + (f32)std::rand() / RAND_MAX * (20.0f   -  0.0f);
    
    c.modulation6   = 0.0f  + (f32)std::rand() / RAND_MAX * (10.0f   -  0.0f);
    
    c.wave7         = std::rand() % (IM_COUNTOF(waves) - 2);
    c.frequency7    = 20.0f + (f32)std::rand() / RAND_MAX * (2000.0f - 20.0f);
    c.vibratoFreq7  = 0.0f  + (f32)std::rand() / RAND_MAX * (100.0f  -  0.0f);
    c.vibratoDepth7 = 0.0f  + (f32)std::rand() / RAND_MAX * (20.0f   -  0.0f);
    
    c.modulation7   = 0.0f  + (f32)std::rand() / RAND_MAX * (10.0f   -  0.0f);
    
    c.wave8         = std::rand() % (IM_COUNTOF(waves) - 2);
    c.frequency8    = 20.0f + (f32)std::rand() / RAND_MAX * (2000.0f - 20.0f);
    c.vibratoFreq8  = 0.0f  + (f32)std::rand() / RAND_MAX * (100.0f  -  0.0f);
    c.vibratoDepth8 = 0.0f  + (f32)std::rand() / RAND_MAX * (20.0f   -  0.0f);
}
void SoundOrganizer() {
    c1 soActive = UI::Begin("Sound Organizer", NULL, uiWindowFlags_NoMove | uiWindowFlags_NoResize | uiWindowFlags_NoCollapse );
    // tellme(std::to_string(soActive), true);
    UI::InputText("File Path", "one \"../\" brings you to the root of the engine.", path, sizeof(path));
    UI::InputText("File Name", "\"whatever you type\".wav", name, sizeof(name));
    const c8* combo_preview = sampleRate[sampleRateIndex];
    if (UI::BeginCombo("Sample Rate", combo_preview, uiComboFlags_Largest)) {
        for (c32 n = 0; n < IM_COUNTOF(sampleRate); n++) {
            const c1 selected = (sampleRateIndex == n);
            if (UI::Selectable(sampleRate[n], selected)) {
                sampleRateIndex = n;
                sample_rate = sampleRateValues[n];
            };
            if (selected) UI::SetItemDefaultFocus();
        }
        UI::EndCombo();
    }
    if (UI::Button("Save")) saveWav();
    UI::SameLine();
    if (UI::Button("Play")) playWav();
    UI::SameLine();
    if (UI::Button("Add Note")) addNote();
    
    UI::BeginChild("##sounds", v2(0, 0));
    c32 selectedNote = -1;
    for (size_t i = 0; i < clips.size();) {
        UI::PushID((c32)i);
        c8 number[32];
        snprintf(number, sizeof(number), "Note %ld", i + 1);
        if (UI::CollapsingHeader(("Note " + std::to_string(i+1)).c_str())) {
            Clip& c = clips[i];
            selectedNote = i;
            c.scroll += UI::GetIO().DeltaTime * c.speed;
            std::vector<f32> graph(c.points);
            f32 phase = 0.0f;
            f32 duration = std::max(c.duration, 0.001f);
            for (s32 i = 0; i < c.points; i++) {
                f32 t = fmodf(c.scroll + (f32)i / (c.points - 1) * c.view, c.duration);
                graph[i] = synth(c, t);
            }
            c8 lines[32];
            snprintf(lines, sizeof(lines), "##lines %ld", i + 1);
            UI::PlotLines(lines, graph.data(), graph.size(), 0, nullptr, -1.0f, 1.0f, v2(UI::GetContentRegionAvail().x, 50));
            UI::SliderFloat("View",  &c.view,   0.001f,   1.0f);
            UI::SliderInt("Points",  &c.points, 128,      1536);
            UI::SliderFloat("Speed", &c.speed,  0.00001f, 0.1f);
            if (UI::Button("Play")) playPreview(i);
            UI::SameLine();
            if (UI::Button("Randomize")) { randomize(clips[i]); playPreview(i); }
            UI::SameLine();
            if (UI::Button("Delete")) { deleteNote(i); UI::PopID(); continue; };
            UI::SliderFloat("Volume", &c.volume, 0.0f, 1.0f, "%03f");
            UI::SliderFloat("Duration", &c.duration, 0.1f, 60.f, "%03f");
            UI::Spacing();
            if (UI::BeginTable("Stats",      3, uiTableFlags_Borders | uiTableFlags_RowBg | uiTableFlags_SizingStretchProp)) {
                UI::TableSetupColumn("Col0");
                UI::TableSetupColumn("N");
                UI::TableSetupColumn("Col1");
                // Data
                UI::TableNextRow();
                UI::TableSetColumnIndex(0);
                UI::SliderFloat("Attack",  &c.attack,  0.0f, 2.0f, "%03f");
                UI::SliderFloat("Decay",   &c.decay,   0.0f, 2.0f, "%03f");
                UI::SliderFloat("Sustain", &c.sustain, 0.0f, 1.0f, "%03f");
                UI::SliderFloat("Release", &c.release, 0.0f, 2.0f, "%03f");
                UI::TableSetColumnIndex(1);
                UI::VSliderFloat("##Noise", v2(36, 80),  &c.noise,   0.0f, 1.0f, "%03f");
                UI::Text("Noise");
                UI::TableSetColumnIndex(2);
                UI::SliderFloat("Reverb Mix",   &c.reverbMix,   0.0f, 1.0f, "%03f");
                UI::SliderFloat("Reverb Decay", &c.reverbDecay, 0.0f, 1.0f, "%03f");
                UI::SliderFloat("Chorus Depth", &c.chorusDepth, 0.0f, 0.3f, "%03f");
                UI::SliderFloat("Chorus Rate",  &c.chorusRate,  0.1f, 4.0f, "%03f");
                UI::EndTable();
            }
            if (UI::BeginTable("Operators1", 7, uiTableFlags_Borders | uiTableFlags_RowBg | uiTableFlags_SizingStretchProp)) {
                UI::TableSetupColumn("Operator 1");
                UI::TableSetupColumn("M 1");
                UI::TableSetupColumn("Operator 2");
                UI::TableSetupColumn("M 2");
                UI::TableSetupColumn("Operator 3");
                UI::TableSetupColumn("M 3");
                UI::TableSetupColumn("Operator 4");
                UI::TableHeadersRow();
                // Data
                UI::TableNextRow();
                UI::TableSetColumnIndex(0);
                UI::Combo(      "Wave 1",  &c.wave1, waves,               5);
                UI::SliderFloat("Freqy 1", &c.frequency1,    20.0f, 2000.0f);
                UI::SliderFloat("Vibro 1", &c.vibratoFreq1,  0.0f,   100.0f);
                UI::SliderFloat("Depth 1", &c.vibratoDepth1, 0.0f,    20.0f);
                UI::TableSetColumnIndex(1);
                UI::VSliderFloat("##Modulation1", v2(20, 100), &c.modulation1, 0.0f, 10.0f);
                UI::TableSetColumnIndex(2);
                UI::Combo(      "Wave 2",  &c.wave2, waves,               5);
                UI::SliderFloat("Freqy 2", &c.frequency2,    20.0f, 2000.0f);
                UI::SliderFloat("Vibro 2", &c.vibratoFreq2,  0.0f,   100.0f);
                UI::SliderFloat("Depth 2", &c.vibratoDepth2, 0.0f,    20.0f);
                UI::TableSetColumnIndex(3);
                UI::VSliderFloat("##Modulation2", v2(20, 100), &c.modulation2, 0.0f, 10.0f);
                UI::TableSetColumnIndex(4);
                UI::Combo(      "Wave 3",  &c.wave3, waves,               5);
                UI::SliderFloat("Freqy 3", &c.frequency3,    20.0f, 2000.0f);
                UI::SliderFloat("Vibro 3", &c.vibratoFreq3,  0.0f,   100.0f);
                UI::SliderFloat("Depth 3", &c.vibratoDepth3, 0.0f,    20.0f);
                UI::TableSetColumnIndex(5);
                UI::VSliderFloat("##Modulation3", v2(20, 100), &c.modulation3, 0.0f, 10.0f);
                UI::TableSetColumnIndex(6);
                UI::Combo(      "Wave 4",  &c.wave4, waves,               5);
                UI::SliderFloat("Freqy 4", &c.frequency4,    20.0f, 2000.0f);
                UI::SliderFloat("Vibro 4", &c.vibratoFreq4,  0.0f,    50.0f);
                UI::SliderFloat("Depth 4", &c.vibratoDepth4, 0.0f,    20.0f);
                UI::EndTable();
            }
            if (UI::BeginTable("Operators2", 8, uiTableFlags_Borders | uiTableFlags_RowBg | uiTableFlags_SizingStretchProp)) {
                UI::TableSetupColumn("M 4");
                UI::TableSetupColumn("Operator 5");
                UI::TableSetupColumn("M 5");
                UI::TableSetupColumn("Operator 6");
                UI::TableSetupColumn("M 6");
                UI::TableSetupColumn("Operator 7");
                UI::TableSetupColumn("M 7");
                UI::TableSetupColumn("Operator 8");
                UI::TableHeadersRow();
                // Data
                UI::TableNextRow();
                UI::TableSetColumnIndex(0);
                UI::VSliderFloat("##Modulation4", v2(20, 100), &c.modulation4, 0.0f, 10.0f);
                UI::TableSetColumnIndex(1);
                UI::Combo(      "Wave 5",  &c.wave5, waves,               5);
                UI::SliderFloat("Freqy 5", &c.frequency5,    20.0f, 2000.0f);
                UI::SliderFloat("Vibro 5", &c.vibratoFreq5,  0.0f,   100.0f);
                UI::SliderFloat("Depth 5", &c.vibratoDepth5, 0.0f,    20.0f);
                UI::TableSetColumnIndex(2);
                UI::VSliderFloat("##Modulation5", v2(20, 100), &c.modulation5, 0.0f, 10.0f);
                UI::TableSetColumnIndex(3);
                UI::Combo(      "Wave 6",  &c.wave6, waves,               5);
                UI::SliderFloat("Freqy 6", &c.frequency6,    20.0f, 2000.0f);
                UI::SliderFloat("Vibro 6", &c.vibratoFreq6,  0.0f,   100.0f);
                UI::SliderFloat("Depth 6", &c.vibratoDepth6, 0.0f,    20.0f);
                UI::TableSetColumnIndex(4);
                UI::VSliderFloat("##Modulation6", v2(20, 100), &c.modulation6, 0.0f, 10.0f);
                UI::TableSetColumnIndex(5);
                UI::Combo(      "Wave 7",  &c.wave7, waves,               5);
                UI::SliderFloat("Freqy 7", &c.frequency7,    20.0f, 2000.0f);
                UI::SliderFloat("Vibro 7", &c.vibratoFreq7,  0.0f,   100.0f);
                UI::SliderFloat("Depth 7", &c.vibratoDepth7, 0.0f,    20.0f);
                UI::TableSetColumnIndex(6);
                UI::VSliderFloat("##Modulation7", v2(20, 100), &c.modulation7, 0.0f, 10.0f);
                UI::TableSetColumnIndex(7);
                UI::Combo(      "Wave 8",  &c.wave8, waves,               5);
                UI::SliderFloat("Freqy 8", &c.frequency8,    20.0f, 2000.0f);
                UI::SliderFloat("Vibro 8", &c.vibratoFreq8,  0.0f,    50.0f);
                UI::SliderFloat("Depth 8", &c.vibratoDepth8, 0.0f,    20.0f);
                UI::EndTable();
            }
        }
        UI::PopID();
        i++;
    }
    UI::EndChild();
    if (soActive &&
        UI::IsKeyDown(INPUT::Key_LeftCtrl) &&
        UI::IsKeyDown(INPUT::Key_LeftShift) &&
        UI::IsKeyPressed(INPUT::Key_H, false))  { soPopup = !soPopup; if (soPopup) UI::OpenPopup("Help##SO"); };
    UI::SetNextWindowPos(UI::GetMainViewport()->GetCenter(), uiCond_Appearing, v2(0.5f, 0.5f));
    if (soPopup) UI::OpenPopup("Help##SO");
    if (UI::BeginPopupModal("Help##SO", &soPopup, uiWindowFlags_AutoResize | uiWindowFlags_NoMove)) {
        if (!soPopup) UI::CloseCurrentPopup();
        UI::SeparatorText("Note");
        UI::Text("    N: Add");
        UI::Text("    R: Randomize");
        UI::Text("Space: Play");
        UI::Text("  Del: Delete");
        UI::EndPopup();
    }
    if (soActive && UI::IsKeyPressed(INPUT::Key_N,      false))                       { addNote(); };
    if (soActive && UI::IsKeyPressed(INPUT::Key_Delete, false) && selectedNote != -1) { deleteNote(selectedNote); };
    if (soActive && UI::IsKeyPressed(INPUT::Key_Space,  false) && selectedNote != -1) { playPreview(selectedNote); };
    if (soActive && UI::IsKeyPressed(INPUT::Key_R,      false) && selectedNote != -1) { randomize(clips[selectedNote]); playPreview(selectedNote); }
}