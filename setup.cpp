//=================================\\
// [ OWNER ]
//     CREATOR  : Vladislav Khudash
//     AGE      : 17
//     LOCATION : Ukraine
//
// [ PINFO ]
//     DATE     : 10.03.2026
//     PROJECT  : PIPEWIRE-SETUPER
//     PLATFORM : LINUX
//=================================\\




#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>




static inline void write_file(const std::string &p, const std::string &dt) {
    std::ofstream f(p);

    if (!f.is_open()) {
        std::cerr << p << " [-]\n";
        return;
    }

    f << dt;

    if (f.fail()) {
        std::cerr << "Failed writing file: " << p << " [*]\n";
        return;
    }

    f.close();
    std::cout << p << " [+]\n";
}


int main() {
    const char *home = getenv("HOME");


    if (!home) {
        std::cerr << "Cannot determine HOME directory [*]\n";
        return 1;
    }


    const std::string uconfig = std::string(home) + "/.config";


    if (!std::filesystem::is_directory(uconfig)) {
        std::cerr << "DO NOT SUPPORT OS [*]\n";
        return 1;
    }


    if (system("which pipewire > /dev/null 2>&1") != 0) {
        std::cerr << "PipeWire not installed [*]\n";
        return 1;
    }


    const std::string pw_dir = uconfig + "/pipewire";

    
    std::error_code ec;
    std::filesystem::create_directories(pw_dir, ec);


    if (ec) {
        std::cerr << "Failed creating PipeWire directory: " << ec.message() << " [*]\n";
        return 1;
    }


    const std::string pipewire_conf       = pw_dir + "/pipewire.conf";
    const std::string pipewire_pulse_conf = pw_dir + "/pipewire-pulse.conf";
    const std::string client_conf         = pw_dir + "/client.conf";
    const std::string client_rt_conf      = pw_dir + "/client-rt.conf";
    const std::string jack_conf           = pw_dir + "/jack.conf";


    std::cout << "Start setuping PipeWire for current USER [*]\n";


    write_file(pipewire_conf, R"CONFIG(context.properties = {
    core.daemon                 = true
    core.name                   = pipewire-0
    default.clock.rate          = 48000
    default.clock.allowed-rates = [48000]
    default.clock.quantum       = 512
    default.clock.min-quantum   = 512
    default.clock.max-quantum   = 1024
    default.clock.quantum-limit = 8192
    link.max-buffers            = 32
    module.x11.bell             = true
    module.access               = true
    module.jackdbus-detect      = true
    vm.overrides                = { default.clock.min-quantum = 512 }
}

context.spa-libs = {
    audio.convert.* = audioconvert/libspa-audioconvert
    avb.* = avb/libspa-avb
    api.alsa.* = alsa/libspa-alsa
    api.v4l2.* = v4l2/libspa-v4l2
    api.libcamera.* = libcamera/libspa-libcamera
    api.bluez5.* = bluez5/libspa-bluez5
    api.vulkan.* = vulkan/libspa-vulkan
    api.jack.* = jack/libspa-jack
    support.* = support/libspa-support
}

context.modules = [
    { name = libpipewire-module-rt 
      args = { nice.level = -2 rt.prio = 50 } 
      flags = [ ifexists nofail ] 
    }
    { name = libpipewire-module-protocol-native }
    { name = libpipewire-module-profiler }
    { name = libpipewire-module-metadata }
    { name = libpipewire-module-spa-device-factory }
    { name = libpipewire-module-spa-node-factory }
    { name = libpipewire-module-client-node }
    { name = libpipewire-module-client-device }
    { name = libpipewire-module-portal flags = [ ifexists nofail ] }
    { name = libpipewire-module-access condition = [ { module.access = true } ] }
    { name = libpipewire-module-adapter }
    { name = libpipewire-module-link-factory }
    { name = libpipewire-module-session-manager }
    { name = libpipewire-module-x11-bell 
      flags = [ ifexists nofail ] 
      condition = [ { module.x11.bell = true } ] 
    }
    { name = libpipewire-module-jackdbus-detect 
      flags = [ ifexists nofail ] 
      condition = [ { module.jackdbus-detect = true } ] 
    }
]

context.objects = [
    { factory = spa-node-factory
      args = {
          factory.name            = api.alsa.pcm.sink
          node.name               = HighQuality-Sink
          node.description        = "ALSA Output (Low-Latency)"
          audio.format            = "S32LE"
          audio.rate              = 48000
          audio.channels          = 2
          resample.quality        = 10
          channelmix.normalize    = false
          channelmix.upmix        = false
          channelmix.upmix-method = psd
          node.latency            = 512/48000
      }
    }
    { factory = spa-node-factory
      args = {
          factory.name     = api.alsa.pcm.source
          node.name        = HighQuality-Source
          node.description = "ALSA Input (Low-Latency)"
          audio.format     = "S32LE"
          audio.rate       = 48000
          audio.channels   = 2
          resample.quality = 10
          node.latency     = 512/48000
      }
    }
]

alsa.properties = {
    alsa.access        = [ MMAP_INTERLEAVED MMAP_NONINTERLEAVED ]
    alsa.format        = [ "S32LE" "F32LE" ]
    alsa.rate          = { min=48000 max=48000 }
    alsa.channels      = { min=2 max=2 }
    alsa.period-bytes  = { min=2048 max=65536 }
    alsa.buffer-bytes  = { min=8192 max=131072 }
    alsa.volume-method = "physical"
}

context.exec = []

pulse.cmd = [
    { cmd = "load-module" args = "module-always-sink" flags = [] }
]

stream.properties = {
    node.latency   = 512/48000
    dither.method  = "shibata"
}

pulse.properties = {
    server.address = ["unix:native"]
    vm.overrides   = { pulse.min.quantum = 512/48000 }
}

pulse.rules = [
    { matches = [] actions = {} }
]
)CONFIG");

    
    write_file(pipewire_pulse_conf, R"(context.properties = {
    default.clock.rate          = 48000
    default.clock.quantum       = 512
    default.clock.min-quantum   = 512
    default.clock.max-quantum   = 1024
    default.clock.quantum-limit = 8192
}

context.spa-libs = {
    audio.convert.* = audioconvert/libspa-audioconvert
    support.*       = support/libspa-support
}

context.modules = [
    { name = libpipewire-module-rt args = { nice.level = -2 } flags = [ ifexists nofail ] }
    { name = libpipewire-module-protocol-native }
    { name = libpipewire-module-client-node }
    { name = libpipewire-module-adapter }
    { name = libpipewire-module-metadata }
    { name = libpipewire-module-protocol-pulse }
]

context.exec = []

pulse.cmd = [
    { cmd = "load-module" args = "module-always-sink" flags = [] }
]

stream.properties = {
    node.latency            = 512/48000
    resample.quality        = 10
    channelmix.normalize    = false
    channelmix.upmix        = false
    channelmix.upmix-method = psd
    audio.format            = "S32LE"
	dither.method           = "shibata"
}

pulse.properties = {
    server.address       = ["unix:native"]
    pulse.default.format = "S32LE"
    vm.overrides         = { pulse.min.quantum = 512/48000 }
}

pulse.rules = [
    { matches = [] actions = {} }
]
)");


    write_file(client_conf, R"(context.properties = {
    log.level = 0
}

context.spa-libs = {
    audio.convert.* = audioconvert/libspa-audioconvert
    api.alsa.*      = alsa/libspa-alsa
    support.*       = support/libspa-support
}

context.modules = [
    { name = libpipewire-module-protocol-native }
    { name = libpipewire-module-client-node }
    { name = libpipewire-module-client-device }
    { name = libpipewire-module-adapter }
    { name = libpipewire-module-metadata }
    { name = libpipewire-module-session-manager }
]

stream.properties = {
	audio.format            = "S32LE" 
	audio.rate              = 48000
    node.latency            = 512/48000
    resample.quality        = 10
	dither.method           = "shibata"
    dither.noise            = 2
    channelmix.normalize    = false
    channelmix.mix-lfe      = true
    channelmix.upmix        = false
    channelmix.upmix-method = psd
}      
)");


    write_file(client_rt_conf, R"(context.properties = {
    log.level                   = 0
    default.clock.rate          = 48000
	default.clock.allowed-rates = [ 44100 48000 ]
    default.clock.quantum       = 512
    default.clock.min-quantum   = 512
    default.clock.max-quantum   = 1024
    default.clock.quantum-limit = 8192
}

context.spa-libs = {
    audio.convert.* = audioconvert/libspa-audioconvert
    api.alsa.*      = alsa/libspa-alsa
    support.*       = support/libspa-support
}

context.modules = [
    { name  = libpipewire-module-rt
      args  = { rt.prio = 50 nice.level = -1 }
      flags = [ ifexists nofail ]
    }
    { name  = libpipewire-module-protocol-native }
    { name  = libpipewire-module-client-node }
    { name  = libpipewire-module-client-device }
    { name  = libpipewire-module-adapter }
    { name  = libpipewire-module-metadata }
    { name  = libpipewire-module-session-manager }
]

context.objects = [
    { factory = spa-device-factory
      args    = { factory.name = api.alsa.enum.udev }
    }
]

stream.properties = {
    node.latency            = 512/48000
    resample.quality        = 10
    dither.method           = "shibata"
    dither.noise            = 2
    channelmix.normalize    = false
    channelmix.mix-lfe      = true
    channelmix.upmix        = false
    channelmix.upmix-method = psd
    audio.format            = "S32LE"
    audio.rate              = 48000
}

alsa.properties = {
    alsa.access        = [ MMAP_INTERLEAVED MMAP_NONINTERLEAVED RW_INTERLEAVED RW_NONINTERLEAVED ]
    alsa.format        = [ FLOAT S32 ]
    alsa.rate          = { min=44100 max=48000 }
    alsa.channels      = { min=2 max=2 }
    alsa.period-bytes  = { min=1024 max=65536 }
    alsa.buffer-bytes  = { min=8192 max=131072 }
    alsa.volume-method = "physical"
}
)");
    

    write_file(jack_conf, R"(context.properties = {
    log.level = 0
}

context.spa-libs = {
    audio.convert.* = audioconvert/libspa-audioconvert
    support.*       = support/libspa-support
}

context.modules = [
    { name = libpipewire-module-rt args = { rt.prio = 50 nice.level = -1 } flags = [ ifexists nofail ] }
    { name = libpipewire-module-protocol-native }
    { name = libpipewire-module-client-node }
    { name = libpipewire-module-metadata }
]

jack.properties = {
    node.latency           = 512/48000
    node.rate              = 48000
    node.quantum           = 512
    node.lock-quantum      = true
    jack.self-connect-mode = allow
    jack.merge-monitor     = false
    resample.quality       = 10
}       
)");


    if (system("systemctl --user restart pipewire.service pipewire-pulse.service wireplumber.service") != 0) {
        std::cerr << "Failed restarting PipeWire services [*]\n";
    }
        

    std::cout << "Setuped PipeWire for current USER [+]\n";
    return 0;
}
