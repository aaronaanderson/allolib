
#include "catch.hpp"

#include "al/core/io/al_MIDI.hpp"

using namespace al;

#ifndef TRAVIS_BUILD

TEST_CASE( "MIDI test" ) {
    RtMidiIn midiInput;
    RtMidiOut midiOutput;
}

TEST_CASE( "MIDI test-old API" ) {
    MIDIIn midiInput;
    MIDIOut midiOutput;
}

#endif
