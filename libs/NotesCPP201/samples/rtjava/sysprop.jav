//===========================================================================
//
//  Module: SystemProperties.java
//
//  Description:
//      A simple Java applet to display the public Java system properties.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

import java.applet.Applet;
import java.awt.*;
import PropertyWrapper;
import ButtonKeyDriver;

public class SystemProperties extends Applet
{
    int             mCurrentProperty;
    PropertyWrapper mProperties;
    ButtonKeyDriver mPrevButton;
    ButtonKeyDriver mNextButton;
    Label           mNameLabel;
    Label           mValueLabel;

        /* Initialize the applet */
    public void init ()
    {
            /* The easy stuff - set the current property    */
            /* and initialize the property wrapper.         */
        mCurrentProperty = 0;
        mProperties = new PropertyWrapper ();
        
            /* Now the fun part - create and initialize     */
            /* the grid bag layout.                         */
        GridBagConstraints gridConstr = new GridBagConstraints ();
        GridBagLayout   mainGrid = new GridBagLayout ();
        
        Font plainFont = new Font ("Helvetica", Font.PLAIN, 14);
        Font boldFont = new Font ("Helvetica", Font.BOLD, 14);
        Font miniFont = new Font ("Helvetica", Font.PLAIN, 12);
        Font titleFont = new Font ("Times", Font.BOLD, 18);

        setBackground (new Color (200, 200, 255));
        setFont (plainFont);
        setLayout (mainGrid);
        
            /* Blank space at top */
        Label   topSpace = new Label ();
        gridConstr.fill = GridBagConstraints.BOTH;
        gridConstr.gridwidth = GridBagConstraints.REMAINDER;
        gridConstr.weighty = 0.5;
        mainGrid.setConstraints (topSpace, gridConstr);
        add (topSpace);

            /* Title */
        Label   titleLabel = new Label ("System Properties", Label.CENTER);
        titleLabel.setForeground (new Color (0, 0, 255));
        titleLabel.setFont (titleFont);
        gridConstr.weighty = 0.0;
        mainGrid.setConstraints (titleLabel, gridConstr);
        add (titleLabel);

            /* Description */
        Label   descLabel = new Label ("Displays Java system properties.", Label.CENTER);
        descLabel.setFont (miniFont);
        mainGrid.setConstraints (descLabel, gridConstr);
        add (descLabel);
        
            /* Spacing */
        Label   descSpace = new Label ();
        mainGrid.setConstraints (descSpace, gridConstr);
        add (descSpace);

            /* Fixed label */
        Label   fixedNameLabel = new Label ("Property name:");
        fixedNameLabel.setFont (boldFont);
        gridConstr.gridwidth = 1;
        gridConstr.weighty = 0.0;
        gridConstr.insets = new Insets (0, 10, 0, 10);
        mainGrid.setConstraints (fixedNameLabel, gridConstr);
        add (fixedNameLabel);
        
            /* Property name label */
        mNameLabel = new Label (
            mProperties.getPropertyName (mCurrentProperty));
        gridConstr.gridwidth = GridBagConstraints.REMAINDER;
        gridConstr.insets = new Insets (0, 0, 0, 0);
        gridConstr.weightx = 1.0;
        mainGrid.setConstraints (mNameLabel, gridConstr);
        add (mNameLabel);
        
            /* Fixed label */
        Label   fixedValueLabel = new Label ("Value:");
        fixedValueLabel.setFont (boldFont);
        gridConstr.gridwidth = 1;
        gridConstr.insets = new Insets (0, 10, 0, 10);
        gridConstr.weightx = 0.0;
        mainGrid.setConstraints (fixedValueLabel, gridConstr);
        add (fixedValueLabel);
        
            /* Property value label */
        mValueLabel = new Label (
            mProperties.getPropertyValue (mCurrentProperty));
        gridConstr.gridwidth = GridBagConstraints.REMAINDER;
        gridConstr.insets = new Insets (0, 0, 0, 0);
        gridConstr.weightx = 1.0;
        mainGrid.setConstraints (mValueLabel, gridConstr);
        add (mValueLabel);
        
            /* Spacing */
        Label   midSpace = new Label ();
        gridConstr.weightx = 0.0;
        mainGrid.setConstraints (midSpace, gridConstr);
        add (midSpace);

        PanelKeyDriver buttonPanel = new PanelKeyDriver ();
        GridBagLayout   buttonGrid = new GridBagLayout ();
        
        buttonPanel.setLayout (buttonGrid);

            /* Space to left of buttons */
        Label   leftGap = new Label ();
        gridConstr.gridwidth = 1;
        gridConstr.weightx = 1.0;
        buttonGrid.setConstraints (leftGap, gridConstr);
        buttonPanel.add (leftGap);

            /* "Prev" button */
        mPrevButton = new ButtonKeyDriver ("<< Prev");
        gridConstr.weightx = 0.0;
        buttonGrid.setConstraints (mPrevButton, gridConstr);
        buttonPanel.add (mPrevButton);
        
            /* A gap in the middle */
        Label   midGap = new Label ();
        gridConstr.weightx = 0.1;
        buttonGrid.setConstraints (midGap, gridConstr);
        buttonPanel.add (midGap);
        
            /* "Next" button */
        mNextButton = new ButtonKeyDriver ("Next >>");
        gridConstr.weightx = 0.0;
        buttonGrid.setConstraints (mNextButton, gridConstr);
        buttonPanel.add (mNextButton);
        
            /* Gap on the right */
        Label   rightGap = new Label ();
        gridConstr.gridwidth = GridBagConstraints.REMAINDER;
        gridConstr.weightx = 1.0;
        buttonGrid.setConstraints (rightGap, gridConstr);
        buttonPanel.add (rightGap);

        gridConstr.weightx = 0.0;
        mainGrid.setConstraints (buttonPanel, gridConstr);
        add (buttonPanel);
        
            /* Blank space on the bottom */
        Label   bottomSpace = new Label ();
        gridConstr.gridheight = GridBagConstraints.REMAINDER;
        gridConstr.gridwidth = GridBagConstraints.REMAINDER;
        gridConstr.weightx = 0.0;
        gridConstr.weighty = 1.0;
        mainGrid.setConstraints (bottomSpace, gridConstr);
        add (bottomSpace);
        
        mPrevButton.disable ();
        mNextButton.requestFocus ();

        validate ();
    }

        /* Process events */
    public boolean action (
        Event   theEvent,
        Object  theObject
    ) {
        Object  target = theEvent.target;
        
        if (target == mPrevButton)
        {
            if (mCurrentProperty > 0)
            {
                mCurrentProperty--;
                mNameLabel.setText (mProperties.getPropertyName (mCurrentProperty));
                mValueLabel.setText (mProperties.getPropertyValue (mCurrentProperty));
                validate ();
            }
            
            if ((!mNextButton.isEnabled ()) &&
                (mCurrentProperty < (mProperties.getPropertyCount () - 1)))
                    mNextButton.enable ();

            if (0 == mCurrentProperty)
                mPrevButton.disable ();

            return (true);
        }
        else if (target == mNextButton)
        {
            if (mCurrentProperty < (mProperties.getPropertyCount () - 1))
            {
                mCurrentProperty++;
                mNameLabel.setText (mProperties.getPropertyName (mCurrentProperty));
                mValueLabel.setText (mProperties.getPropertyValue (mCurrentProperty));
                validate ();
            }
            
            if ((!mPrevButton.isEnabled ()) && (mCurrentProperty > 0))
                mPrevButton.enable ();

            if ((mProperties.getPropertyCount () - 1) == mCurrentProperty)
                mNextButton.disable ();

            return (true);
        }
        
        return (false);
    }

        /* Process keystrokes */
    public boolean keyDown (
        Event   theEvent,
        int     theKey
    ) {
        if ((Event.KEY_ACTION == theEvent.id) && (Event.LEFT == theEvent.key))
        {
            Event triggerButton = new Event (mPrevButton, theEvent.when,
                Event.KEY_PRESS, theEvent.x, theEvent.y, '\n', theEvent.modifiers);
            
            mPrevButton.requestFocus ();
            
            return (mPrevButton.keyDown (triggerButton, '\n'));
        }
        else if ((Event.KEY_ACTION == theEvent.id) && (Event.RIGHT == theEvent.key))

        {
            Event triggerButton = new Event (mNextButton, theEvent.when,
                Event.KEY_PRESS, theEvent.x, theEvent.y, '\n', theEvent.modifiers);
            
            mNextButton.requestFocus ();
            
            return (mNextButton.keyDown (triggerButton, '\n'));
        }
        
        return (false);
    }
}
