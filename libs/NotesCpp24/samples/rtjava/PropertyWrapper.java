//===========================================================================
//
//  Module: PropertyWrapper.java
//
//  Description:
//      Wraps the system properties with an interface suited to the step-
//      by-step user interface for the SystemProperties applet.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

import java.util.Properties;

    /* The class System.Properties has an interface that    */
    /* doesn't fit the user interface, so let's build a     */
    /* wrapper class that fits the user interface better.   */
public class PropertyWrapper
{
    private int mPropertyCount = 0;
    private String [] mPropertyNames =
    {
        "java.class.version",
        "java.vendor",
        "java.vendor.url",
        "java.version",
        "file.separator",
        "line.separator",
        "path.separator",
        "os.arch",
        "os.name",
        "os.version",
        "user.name"
    };

        /* Constructor */
    PropertyWrapper ()
    {
        mPropertyCount = mPropertyNames.length;
    }

        /* Return the number of properties */
    public int getPropertyCount ()
    {
        return (mPropertyCount);
    }

        /* Return the name of property "n" */
    public String getPropertyName (
        int index
    ) {
        return (mPropertyNames[index]);
    }

        /* Return the value of property "n" */
    public String getPropertyValue (
        int index
    ) {
        try
        {
            return (System.getProperty (mPropertyNames[index]));
        }
        catch (SecurityException e)
        {
            return ("*** Not available:  Security restriction ***");
        }
    }
}
