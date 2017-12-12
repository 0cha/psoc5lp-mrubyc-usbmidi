class MIDI
  NOTE_ON  = 0x90
  NOTE_OFF = 0x80

  SCALES = {
    b_minor_penta: [2, 5, 7, 9, 12, 14]
  }
  
  def send_note_on(note)
    usbmidi_send(NOTE_ON, note, 100)
  end

  def send_note_off(note)
    usbmidi_send(NOTE_OFF, note)
  end

  def set_oct(oct)
    if(sw0_read() == 0)
      if(oct != 0)
        oct = oct + 1
      end
      if(oct > 6)
        oct = 4
      end
      puts oct
    end
    return oct
  end
  
  def read_note(scale, oct)
    _oct = oct * 12
    return SCALES[scale][0] + _oct if sw_up_read()    == 0
    return SCALES[scale][1] + _oct if sw_left_read()  == 0
    return SCALES[scale][2] + _oct if sw_down_read()  == 0
    return SCALES[scale][3] + _oct if sw_right_read() == 0
    return SCALES[scale][4] + _oct if sw1_read()      == 0
    return SCALES[scale][5] + _oct if sw2_read()      == 0
    return false
  end
end

midi = MIDI.new
oct = 5
current_note = nil
previous_note = nil

while true
  oct = midi.set_oct(oct)
  if(usbmidi_is_configuration_changed != 0)
    if(usbmidi_get_configuration != 0 )
      puts 'midi initialize...'
      usbmidi_initialize()
      puts 'midi initialize done..'
    end
  end
  if(usbmidi_get_configuration != 0)
    usbmidi_in_and_out_service()
    current_note = midi.read_note(:b_minor_penta, oct)
    if(current_note != previous_note)
      midi.send_note_off(previous_note) if previous_note
      midi.send_note_on(current_note) if current_note != false
      previous_note = current_note
    end
  end
  
end
