/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2015 - ROLI Ltd.

   Permission is granted to use this software under the terms of either:
   a) the GPL v2 (or any later version)
   b) the Affero GPL v3

   Details of these licenses can be found at: www.gnu.org/licenses

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.juce.com for more information.

  ==============================================================================
*/

#ifndef JUCE_MPEZONELAYOUT_H_INCLUDED
#define JUCE_MPEZONELAYOUT_H_INCLUDED


//==============================================================================
/**
    This class represents the current MPE zone layout of a device
    capable of handling MPE.

    Use the MPEMessages helper class to convert the zone layout represented
    by this object to MIDI message sequences that you can send to an Expressive
    MIDI device to set its zone layout, add zones etc.

    @see MPEZone, MPEInstrument
*/
class JUCE_API  MPEZoneLayout
{
public:
    /** Default constructor.

        This will create a layout with no MPE zones.
        You can add an MPE zone using the method addZone.
    */
    MPEZoneLayout() noexcept;

    /** Adds a new MPE zone to the layout.

        @param newZone  The zone to add.

        @return  true if the zone was added without modifying any other zones
                 added previously to the same zone layout object (if any);
                 false if any existing MPE zones had to be truncated
                 or deleted entirely in order to to add this new zone.
                 (Note: the zone itself will always be added with the channel bounds
                 that were specified; this will not fail.)
    */
    bool addZone (MPEZone newZone);

    /** Removes all currently present MPE zones. */
    void clearAllZones();

    /** Pass incoming MIDI messages to an object of this class if you want the
        zone layout to properly react to MPE RPN messages like an
        MPE device.
        MPEMessages::rpnNumber will add or remove zones; RPN 0 will
        set the per-note or master pitchbend ranges.

        Any other MIDI messages will be ignored by this class.

        @see MPEMessages
    */
    void processNextMidiEvent (const MidiMessage& message);

    /** Pass incoming MIDI buffers to an object of this class if you want the
        zone layout to properly react to MPE RPN messages like an
        MPE device.
        MPEMessages::rpnNumber will add or remove zones; RPN 0 will
        set the per-note or master pitchbend ranges.

        Any other MIDI messages will be ignored by this class.

        @see MPEMessages
     */
    void processNextMidiBuffer (const MidiBuffer& buffer);

    /** Returns the current number of MPE zones. */
    int getNumZones() const noexcept;

    /** Returns a pointer to the MPE zone at the given index,
        or nullptr if there is no such zone.
    */
    MPEZone* getZoneByIndex (int index) const noexcept;

    /** Returns a pointer to the zone which uses the specified channel (1-16),
        or nullptr if there is no such zone.
    */
    MPEZone* getZoneByChannel (int midiChannel) const noexcept;

    /** Returns a pointer to the zone which has the specified channel (1-16)
        as its master channel, or nullptr if there is no such zone.
    */
    MPEZone* getZoneByMasterChannel (int midiChannel) const noexcept;

    /** Returns a pointer to the zone which has the specified channel (1-16)
        as its first note channel, or nullptr if there is no such zone.
    */
    MPEZone* getZoneByFirstNoteChannel (int midiChannel) const noexcept;

    /** Returns a pointer to the zone which has the specified channel (1-16)
        as one of its note channels, or nullptr if there is no such zone.
    */
    MPEZone* getZoneByNoteChannel (int midiChannel) const noexcept;

private:
    //==========================================================================
    Array<MPEZone> zones;
    MidiRPNDetector rpnDetector;

    void processRpnMessage (MidiRPNMessage);
    void processZoneLayoutRpnMessage (MidiRPNMessage);
    void processPitchbendRangeRpnMessage (MidiRPNMessage);
};


#endif // JUCE_MPEZONELAYOUT_H_INCLUDED
