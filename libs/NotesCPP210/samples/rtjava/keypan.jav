//===========================================================================
//
//  Module: PanelKeyDriver.java
//
//  Description:
//      Since I used a sub-panel in the applet layout, the sub-panel must
//      pass action events up to the applet.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

import java.awt.*;

class PanelKeyDriver extends Panel
{
        /* Void constructor */
    public PanelKeyDriver ()
    {
        super ();
    }

        /* Pass any action events up to the container */
    public boolean action (
        Event   theEvent,
        Object  what
    ) {
        return (getParent().action (theEvent, what));
    }
}
