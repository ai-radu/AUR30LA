#include <iostream>
#include "soundOrganizer.h"

const char* chunk_id       = "RIFF";
const char* chunk_size     = "----"; // 4 bytes
const char* format         = "WAVE";
const char* subchunk1_id   = "fmt ";
const char* subchunk2_id   = "data";
const char* subchunk2_size = "----"; // 4 bytes
const int subchunk1_size   = 16;
const int audio_format     = 1;
const int num_channels     = 2;
const int bits_per_sample  = 16;
const int block_align      = num_channels * (bits_per_sample / 8);
const char* waves[] = { "Sine", "Square", "Saw", "Triangle", "Noise" };
static const int sampleRateValues[] = {
    8000, 11025, 16000, 22050, 24000, 32000, 44100,
    48000, 88200, 96000, 176400, 192000, 352800, 384000
};
static const char* sampleRate[] = {
    "8000", "11025", "16000", "22050", "24000", "32000", "44100",
    "48000", "88200", "96000", "176400", "192000", "352800", "384000"
};
int sampleRateIndex = 6;
int sample_rate = sampleRateValues[6];
struct Operator {
    int   wave          = 0;
    float frequency     = 440.0f;
    float vibratoFreq   = 5.0f;
    float vibratoDepth  = 5.0f;
    float modulation    = 0.0f;
};
struct Clip {
    float scroll        = 0.0f;
    float speed         = 0.005;
    int   points        = 512;
    float view          = 0.025f;
    
    float volume        = 0.3f;
    float duration      = 2.0f;
    
    float attack        = 0.01f;
    float decay         = 0.1f;
    float sustain       = 0.8f;
    float release       = 0.2f;
    float noise         = 0.0f;
    
    float reverbMix     = 0.3f;
    float reverbDecay   = 0.3f;
    float chorusDepth   = 0.2f;
    float chorusRate    = 0.8f;

    int   wave1         = 0;
    float frequency1    = 110.0f;
    float vibratoFreq1  = 1.0f;
    float vibratoDepth1 = 1.0f;
    
    float modulation1   = 1.2f;
    
    int   wave2         = 0;
    float frequency2    = 220.0f;
    float vibratoFreq2  = 2.22f;
    float vibratoDepth2 = 2.22f;
    
    float modulation2   = 2.4f;
    
    int   wave3         = 0;
    float frequency3    = 330.0f;
    float vibratoFreq3  = 3.33f;
    float vibratoDepth3 = 3.33f;
    
    float modulation3   = 3.6f;
    
    int   wave4         = 0;
    float frequency4    = 440.0f;
    float vibratoFreq4  = 4.44f;
    float vibratoDepth4 = 4.44f;
    
    float modulation4   = 2.4f;
    
    int   wave5         = 0;
    float frequency5    = 550.0f;
    float vibratoFreq5  = 5.55f;
    float vibratoDepth5 = 5.55f;
    
    float modulation5   = 1.2f;
    
    int   wave6         = 0;
    float frequency6    = 660.0f;
    float vibratoFreq6  = 6.66f;
    float vibratoDepth6 = 6.66f;
    
    float modulation6   = 2.4f;
    
    int   wave7         = 0;
    float frequency7    = 770.0f;
    float vibratoFreq7  = 7.77f;
    float vibratoDepth7 = 7.77f;
    
    float modulation7   = 3.6f;
    
    int   wave8         = 0;
    float frequency8    = 880.0f;
    float vibratoFreq8  = 8.88f;
    float vibratoDepth8 = 8.88f;
};
struct stereo {
    int16_t left;
    int16_t right;
};
ma_engine engine;
ma_sound sound;
ma_sound previewSound;
ma_audio_buffer previewBuffer;
std::vector<Clip> clips;
char name[64] = "test";
char path[64] = "../assets/audio/soundOrganizer/";
float noteToFreq(int note) { return 440.0f * std::powf(2.0f, (note - 69) / 12.0f); }
// FIXME
float getNoise() {
    static uint32_t seed = 123456789;
    seed = seed * 1664525u + 1013904223u;
    return ((seed & 0xFFFF) / 32768.0f) * 2.0f - 1.0f;
}
float oscillator(int type, float phase) {
    switch (type) {
        case 0: return std::sin(2 * PI * phase); // sine
        case 1: return std::sin(2 * PI * phase) >= 0 ? 1.0f : -1.0f; // square
        case 2: return 2.0f * (phase - std::floor(phase + 0.5f)); // saw
        case 3: return 2.0f * std::fabs(2 * (phase - std::floor(phase + 0.5f))) - 1.0f; // triangle
        case 4: return getNoise(); // noise
        default: return 0.0f;
    }
}
float getEnvelope(const Clip& clip, float t) {
    float attack  = std::max(clip.attack,  0.0001f);
    float decay   = std::max(clip.decay,   0.0001f);
    float release = std::max(clip.release, 0.0001f);
    if (t < attack)         return t / attack;
    if (t < attack + decay) return 1.0f + (t - attack) / decay * (clip.sustain - 1.0f);
    if (t < clip.duration - release) return clip.sustain;
    float st = (t - (clip.duration - release)) / release;
    return clip.sustain * (1.0f - st);
}
float synth(const Clip& c, float t) {
    float op1 = oscillator(c.wave1, c.frequency1 * t + c.vibratoDepth1 * std::sin(2 * PI * c.vibratoFreq1 * t));
    float op2 = oscillator(c.wave2, c.frequency2 * t + c.vibratoDepth2 * std::sin(2 * PI * c.vibratoFreq2 * t));
    float op3 = oscillator(c.wave3, c.frequency3 * t + c.vibratoDepth3 * std::sin(2 * PI * c.vibratoFreq3 * t));
    float op4 = oscillator(c.wave4, c.frequency4 * t + c.vibratoDepth4 * std::sin(2 * PI * c.vibratoFreq4 * t));
    float op5 = oscillator(c.wave5, c.frequency5 * t + c.vibratoDepth5 * std::sin(2 * PI * c.vibratoFreq5 * t));
    float op6 = oscillator(c.wave6, c.frequency6 * t + c.vibratoDepth6 * std::sin(2 * PI * c.vibratoFreq6 * t));
    float op7 = oscillator(c.wave7, c.frequency7 * t + c.vibratoDepth7 * std::sin(2 * PI * c.vibratoFreq7 * t));
    float op8 = oscillator(c.wave8, c.frequency8 * t + c.vibratoDepth8 * std::sin(2 * PI * c.vibratoFreq8 * t));
    float gain = 1.0f +
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
stereo generate(const Clip& c, float t) {
    float sample = synth(c, t);
    float wet = sample;
    // FIXME chorus
    float chorus = 0.0f;
    if (c.chorusDepth > 0.001f) {
        float lfo1 = std::sin(2 * PI * c.chorusRate * t);
        float lfo2 = std::sin(2 * PI * c.chorusRate * 1.3f * t + 2.0f);
        float m1 = 0.0025f + c.chorusDepth * 0.007f * lfo1;
        float m2 = 0.003f  + c.chorusDepth * 0.007f * lfo2;
        float chorus1 = (t > m1) ? synth(c, t - m1) : sample;
        float chorus2 = (t > m2) ? synth(c, t - m2) : sample;
        wet += (chorus1 + chorus2) * 0.35f * c.chorusDepth;
    }
    // reverb
    if (c.reverbMix > 0.001f) {
        float fb = 0.6f + c.reverbDecay * 0.35f;
        float r1 = (t > 0.035f) ? synth(c, t - 0.037f) * fb : 0.0f;
        float r2 = (t > 0.059f) ? synth(c, t - 0.059f) * fb * 0.85f : 0.0f;
        float r3 = (t > 0.091f) ? synth(c, t - 0.091f) * fb * 0.7f  : 0.0f;
        float r4 = (t > 0.131f) ? synth(c, t - 0.131f) * fb * 0.55f : 0.0f;
        wet += (r1 + r2 + r3 + r4) * c.reverbMix * 1.5f;
    }
    float noise = getNoise() * c.noise;
    float envelope = getEnvelope(c, t);
    float final = (wet + noise) * envelope * c.volume;
    final = std::clamp(final, -1.0f, 1.0f);
    int16_t value = (int16_t)(final * 32767.0f);
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
    if (!file.is_open()) { say("[WARNING] soundOrganizer.cpp > saveWav() ? !file.is_open()"); return; }
    uint32_t totalSamples = 0;
    for (const auto& clip : clips) { totalSamples += static_cast<uint32_t>(sample_rate * clip.duration); }
    uint16_t wavaudioformat = audio_format;
    uint16_t wavnumchannels = num_channels;
    uint16_t wavblockalign  = block_align;
    uint16_t wavbitspersample = bits_per_sample;
    
    uint32_t wavsamplerate  = sample_rate;
    uint32_t subchunk2_size = totalSamples * num_channels * (bits_per_sample / 8);
    uint32_t chunkSize      = 36 + subchunk2_size;
    uint32_t byteRate       = sample_rate  * num_channels * (bits_per_sample / 8);
    file.write(chunk_id,                                       4);
    file.write(reinterpret_cast<char*>(&chunkSize),            4);
    file.write(format,                                         4);
    file.write(subchunk1_id,                                   4);
    file.write(reinterpret_cast<const char*>(&subchunk1_size), 4);
    file.write(reinterpret_cast<char*>(&wavaudioformat),       2);
    file.write(reinterpret_cast<char*>(&wavnumchannels),       2);
    file.write(reinterpret_cast<char*>(&wavsamplerate),        4);
    file.write(reinterpret_cast<char*>(&byteRate),             4);
    file.write(reinterpret_cast<char*>(&wavblockalign),        2);
    file.write(reinterpret_cast<char*>(&wavbitspersample),     2);
    file.write(subchunk2_id,                                   4);
    file.write(reinterpret_cast<char*>(&subchunk2_size),       4);
    for (const auto& clip : clips) {
        int samples = (int)(sample_rate * clip.duration);
        for (int i = 0; i < samples; i++) {
            float t  = (float)i / sample_rate;
            stereo s = generate(clip, t);
            file.write(reinterpret_cast<char*>(&s.left),  2);
            file.write(reinterpret_cast<char*>(&s.right), 2);
        };
    };
}
void playPreview(size_t index) {
    if (index >= clips.size()) { say("[WARNING] playPreview() ? clipIndex >= clips.size()"); return; };
    const Clip& clip = clips[index];
    int sampleRateEngine = ma_engine_get_sample_rate(&engine);
    int total = (int)(sampleRateEngine * clip.duration);
    static std::vector<int16_t> pcm;
    pcm.resize(total * 2);
    for (int i = 0; i < total; i++) {
        float t  = (float)i / sampleRateEngine;
        stereo s = generate(clip, t);
        pcm[i * 2]     = s.left;
        pcm[i * 2 + 1] = s.right;
    };
    ma_audio_buffer_config config = ma_audio_buffer_config_init(ma_format_s16, 2, total, pcm.data(), nullptr);
    static bool previewBufferInit = false;
    if (previewBufferInit) ma_audio_buffer_uninit(&previewBuffer);
    ma_audio_buffer_init(&config, &previewBuffer);
    previewBufferInit = true;
    
    ma_sound_stop(&previewSound);
    static bool previewSoundInit = false;
    if (previewSoundInit) ma_sound_uninit(&previewSound);
    previewSoundInit = true;
    ma_sound_init_from_data_source(&engine, &previewBuffer, MA_SOUND_FLAG_DECODE, nullptr, &previewSound);
    ma_sound_start(&previewSound);
}
void playWav() {
    std::string entire = std::string(path) + name + ".wav";
    ma_sound_uninit(&sound);
    if(ma_sound_init_from_file(&engine, entire.c_str(), 0, nullptr, nullptr, &sound) != MA_SUCCESS) {
        say("[WARNING] soundOrganizer.cpp > playWav() ? !ma_sound_init_from_file");
        return;
    }
    ma_sound_start(&sound);
}
// TODO make it nicer
void soundOrganizer() {
    UI::PushStyleVar(uiStyleVar_WindowPadding, vec2(0, 0));
    UI::Begin("Sound Organizer", NULL,
        uiWindowFlags_NoMove |
        uiWindowFlags_NoResize |
        uiWindowFlags_NoCollapse
    );
    UI::PopStyleVar();
    
    UI::InputTextWithHint("File Path", "one \"../\" brings you to the root of the engine.", path, sizeof(path));
    UI::InputTextWithHint("File Name", "\"whatever you type\".wav", name, sizeof(name));
    const char* combo_preview = sampleRate[sampleRateIndex];
    if (UI::BeginCombo("Sample Rate", combo_preview, uiComboFlags_Largest)) {
        for (int n = 0; n < IM_ARRAYSIZE(sampleRate); n++) {
            const bool selected = (sampleRateIndex == n);
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
    if (UI::BeginPopupContextItem("popUp", uiPopupFlags_MouseButtonRight)) {
        UI::Text("Edit name:");
        UI::InputText("##edit", name, IM_COUNTOF(name));
        if (UI::Button("Close"))
            UI::CloseCurrentPopup();
        UI::EndPopup();
    }
    UI::SameLine();
    if (UI::Button("Add Note")) {
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
        // say(std::to_string(clips.size()).c_str());
    };
    
    UI::BeginChild("##sounds", vec2(0, 0));
    for (size_t i = 0; i < clips.size();) {
        UI::PushID((int)i);
        char number[32];
        snprintf(number, sizeof(number), "Note %ld", i + 1);
        if (UI::CollapsingHeader(("Note " + std::to_string(i+1)).c_str())) {
            Clip& c = clips[i];
            c.scroll += UI::GetIO().DeltaTime * c.speed;
            std::vector<float> graph(c.points);
            float phase = 0.0f;
            float duration = std::max(c.duration, 0.001f);
            for (int i = 0; i < c.points; i++) {
                float t = fmodf(c.scroll + (float)i / (c.points - 1) * c.view, c.duration);
                graph[i] = synth(c, t);
            }
            char lines[32];
            snprintf(lines, sizeof(lines), "##lines %ld", i + 1);
            UI::PlotLines(lines, graph.data(), graph.size(), 0, nullptr, -1.0f, 1.0f, vec2(UI::GetContentRegionAvail().x, 50));
            UI::SliderFloat("View",  &c.view,   0.001f,   1.0f);
            UI::SliderInt("Points",  &c.points, 128,      1536);
            UI::SliderFloat("Speed", &c.speed,  0.00001f, 0.1f);
            if (UI::Button("Play")) playPreview(i);
            UI::SameLine();
            if (UI::Button("Randomize")) { // fixme ?
                c.reverbMix     = 0.0f  + (float)std::rand() / RAND_MAX * (1.0f    -  0.0f);
                c.reverbDecay   = 0.0f  + (float)std::rand() / RAND_MAX * (1.0f    -  0.0f);
                c.chorusDepth   = 0.0f  + (float)std::rand() / RAND_MAX * (0.3f    -  0.0f);
                c.chorusRate    = 0.0f  + (float)std::rand() / RAND_MAX * (4.0f    -  0.0f);
                
                c.wave1         = std::rand() % (IM_ARRAYSIZE(waves) - 2);
                c.frequency1    = 20.0f + (float)std::rand() / RAND_MAX * (2000.0f - 20.0f);
                c.vibratoFreq1  = 0.0f  + (float)std::rand() / RAND_MAX * (100.0f  -  0.0f);
                c.vibratoDepth1 = 0.0f  + (float)std::rand() / RAND_MAX * (20.0f   -  0.0f);
                
                c.modulation1   = 0.0f  + (float)std::rand() / RAND_MAX * (10.0f   -  0.0f);
                
                c.wave2         = std::rand() % (IM_ARRAYSIZE(waves) - 2);
                c.frequency2    = 20.0f + (float)std::rand() / RAND_MAX * (2000.0f - 20.0f);
                c.vibratoFreq2  = 0.0f  + (float)std::rand() / RAND_MAX * (100.0f  -  0.0f);
                c.vibratoDepth2 = 0.0f  + (float)std::rand() / RAND_MAX * (20.0f   -  0.0f);
                
                c.modulation2   = 0.0f  + (float)std::rand() / RAND_MAX * (10.0f   -  0.0f);
                
                c.wave3         = std::rand() % (IM_ARRAYSIZE(waves) - 2);
                c.frequency3    = 20.0f + (float)std::rand() / RAND_MAX * (2000.0f - 20.0f);
                c.vibratoFreq3  = 0.0f  + (float)std::rand() / RAND_MAX * (100.0f  -  0.0f);
                c.vibratoDepth3 = 0.0f  + (float)std::rand() / RAND_MAX * (20.0f   -  0.0f);
                
                c.modulation3   = 0.0f  + (float)std::rand() / RAND_MAX * (10.0f   -  0.0f);
                
                c.wave4         = std::rand() % (IM_ARRAYSIZE(waves) - 2);
                c.frequency4    = 20.0f + (float)std::rand() / RAND_MAX * (2000.0f - 20.0f);
                c.vibratoFreq4  = 0.0f  + (float)std::rand() / RAND_MAX * (100.0f  -  0.0f);
                c.vibratoDepth4 = 0.0f  + (float)std::rand() / RAND_MAX * (20.0f   -  0.0f);
                
                c.modulation4   = 0.0f  + (float)std::rand() / RAND_MAX * (10.0f   -  0.0f);
                
                c.wave5         = std::rand() % (IM_ARRAYSIZE(waves) - 2);
                c.frequency5    = 20.0f + (float)std::rand() / RAND_MAX * (2000.0f - 20.0f);
                c.vibratoFreq5  = 0.0f  + (float)std::rand() / RAND_MAX * (100.0f  -  0.0f);
                c.vibratoDepth5 = 0.0f  + (float)std::rand() / RAND_MAX * (20.0f   -  0.0f);
                
                c.modulation5   = 0.0f  + (float)std::rand() / RAND_MAX * (10.0f   -  0.0f);
                
                c.wave6         = std::rand() % (IM_ARRAYSIZE(waves) - 2);
                c.frequency6    = 20.0f + (float)std::rand() / RAND_MAX * (2000.0f - 20.0f);
                c.vibratoFreq6  = 0.0f  + (float)std::rand() / RAND_MAX * (100.0f  -  0.0f);
                c.vibratoDepth6 = 0.0f  + (float)std::rand() / RAND_MAX * (20.0f   -  0.0f);
                
                c.modulation6   = 0.0f  + (float)std::rand() / RAND_MAX * (10.0f   -  0.0f);
                
                c.wave7         = std::rand() % (IM_ARRAYSIZE(waves) - 2);
                c.frequency7    = 20.0f + (float)std::rand() / RAND_MAX * (2000.0f - 20.0f);
                c.vibratoFreq7  = 0.0f  + (float)std::rand() / RAND_MAX * (100.0f  -  0.0f);
                c.vibratoDepth7 = 0.0f  + (float)std::rand() / RAND_MAX * (20.0f   -  0.0f);
                
                c.modulation7   = 0.0f  + (float)std::rand() / RAND_MAX * (10.0f   -  0.0f);
                
                c.wave8         = std::rand() % (IM_ARRAYSIZE(waves) - 2);
                c.frequency8    = 20.0f + (float)std::rand() / RAND_MAX * (2000.0f - 20.0f);
                c.vibratoFreq8  = 0.0f  + (float)std::rand() / RAND_MAX * (100.0f  -  0.0f);
                c.vibratoDepth8 = 0.0f  + (float)std::rand() / RAND_MAX * (20.0f   -  0.0f);
                playPreview(i);
            }
            UI::SameLine();
            if (UI::Button("Delete")) { clips.erase(clips.begin() + i); UI::PopID(); continue; };
            UI::SliderFloat("Volume",         &c.volume,        0.0f,     1.0f, "%03f");
            UI::SliderFloat("Duration",       &c.duration,      0.1f,     60.f, "%03f");
            UI::Spacing();
            if (UI::BeginTable("Stats", 3, uiTableFlags_Borders | uiTableFlags_RowBg | uiTableFlags_SizingStretchProp)) {
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
                UI::VSliderFloat("##Noise", vec2(36, 80),  &c.noise,   0.0f, 1.0f, "%03f");
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
                UI::VSliderFloat("##Modulation1", vec2(20, 100), &c.modulation1, 0.0f, 10.0f);
                UI::TableSetColumnIndex(2);
                UI::Combo(      "Wave 2",  &c.wave2, waves,               5);
                UI::SliderFloat("Freqy 2", &c.frequency2,    20.0f, 2000.0f);
                UI::SliderFloat("Vibro 2", &c.vibratoFreq2,  0.0f,   100.0f);
                UI::SliderFloat("Depth 2", &c.vibratoDepth2, 0.0f,    20.0f);
                UI::TableSetColumnIndex(3);
                UI::VSliderFloat("##Modulation2", vec2(20, 100), &c.modulation2, 0.0f, 10.0f);
                UI::TableSetColumnIndex(4);
                UI::Combo(      "Wave 3",  &c.wave3, waves,               5);
                UI::SliderFloat("Freqy 3", &c.frequency3,    20.0f, 2000.0f);
                UI::SliderFloat("Vibro 3", &c.vibratoFreq3,  0.0f,   100.0f);
                UI::SliderFloat("Depth 3", &c.vibratoDepth3, 0.0f,    20.0f);
                UI::TableSetColumnIndex(5);
                UI::VSliderFloat("##Modulation3", vec2(20, 100), &c.modulation3, 0.0f, 10.0f);
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
                UI::VSliderFloat("##Modulation4", vec2(20, 100), &c.modulation4, 0.0f, 10.0f);
                UI::TableSetColumnIndex(1);
                UI::Combo(      "Wave 5",  &c.wave5, waves,               5);
                UI::SliderFloat("Freqy 5", &c.frequency5,    20.0f, 2000.0f);
                UI::SliderFloat("Vibro 5", &c.vibratoFreq5,  0.0f,   100.0f);
                UI::SliderFloat("Depth 5", &c.vibratoDepth5, 0.0f,    20.0f);
                UI::TableSetColumnIndex(2);
                UI::VSliderFloat("##Modulation5", vec2(20, 100), &c.modulation5, 0.0f, 10.0f);
                UI::TableSetColumnIndex(3);
                UI::Combo(      "Wave 6",  &c.wave6, waves,               5);
                UI::SliderFloat("Freqy 6", &c.frequency6,    20.0f, 2000.0f);
                UI::SliderFloat("Vibro 6", &c.vibratoFreq6,  0.0f,   100.0f);
                UI::SliderFloat("Depth 6", &c.vibratoDepth6, 0.0f,    20.0f);
                UI::TableSetColumnIndex(4);
                UI::VSliderFloat("##Modulation6", vec2(20, 100), &c.modulation6, 0.0f, 10.0f);
                UI::TableSetColumnIndex(5);
                UI::Combo(      "Wave 7",  &c.wave7, waves,               5);
                UI::SliderFloat("Freqy 7", &c.frequency7,    20.0f, 2000.0f);
                UI::SliderFloat("Vibro 7", &c.vibratoFreq7,  0.0f,   100.0f);
                UI::SliderFloat("Depth 7", &c.vibratoDepth7, 0.0f,    20.0f);
                UI::TableSetColumnIndex(6);
                UI::VSliderFloat("##Modulation7", vec2(20, 100), &c.modulation7, 0.0f, 10.0f);
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
    // UI::End();
}