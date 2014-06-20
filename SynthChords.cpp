#include "SynthChords.h"

SynthChords::SynthChords(Inputs* inputs)
{
  	
	ModuleWavetableOsc *wavetable_osc1 = new ModuleWavetableOsc();
	ModuleWavetableOsc *wavetable_osc2 = new ModuleWavetableOsc();
	ModuleWavetableOsc *wavetable_osc3 = new ModuleWavetableOsc();

	ModuleQuantizer *quantizer = new ModuleQuantizer();
	ModuleExtClock *ext_clock = new ModuleExtClock(120, EIGHTH_NOTE_CLOCK_DIVISION);
	ModuleChords *chords = new ModuleChords();
	ModuleMixer3 *mixer_3 = new ModuleMixer3();

	quantizer->cv_input = inputs->sr;
	quantizer->scale_input = inputs->param1;

	chords->root_note_input = quantizer;
	chords->chord_input = inputs->mod;

	wavetable_osc1->wavetable_input  = new ModuleConstant(0);
	wavetable_osc1->frequency_input  = chords->note_1_output;

	wavetable_osc2->wavetable_input = inputs->param2;
	wavetable_osc2->frequency_input  = chords->note_2_output;

	wavetable_osc3->wavetable_input = inputs->param3;
	wavetable_osc3->frequency_input  = chords->note_3_output;

	mixer_3->input_1 = wavetable_osc1;
	mixer_3->input_2 = wavetable_osc2;
	mixer_3->input_3 = wavetable_osc3;

	this->last_module = mixer_3;

}