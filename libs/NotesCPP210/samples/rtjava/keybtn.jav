//===========================================================================
//
//  Module: ButtonKeyDriver.java
//
//  Description:
//      An extension of the Button class that responds to the "Enter" key.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

import java.awt.*;

class ButtonKeyDriver extends Button
{
        /* Void constructor */
    public ButtonKeyDriver ()
    {
        super ();
    }

        /* Labelled button constructor */
    public ButtonKeyDriver (
        String  label
    ) {
        super (label);
    }

        /* Process a keystroke */
    public boolean keyDown (
        Event   theEvent,
        int     theKey
    ) {
        if ('\n' == theKey)
        {
            Event triggerEvent = new Event (
                this,
                theEvent.when,
                Event.ACTION_EVENT,
                theEvent.x,
                theEvent.y,
                theKey,
                theEvent.modifiers);
            return (getParent().action (triggerEvent, this));
        }
        
        return (false);
    }
}
