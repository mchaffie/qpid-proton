/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */
package org.apache.qpid.proton;

import java.io.File;
import java.net.URISyntaxException;
import java.net.URL;
import java.util.logging.Logger;

import org.junit.Test;
import org.python.core.PyException;
import org.python.util.PythonInterpreter;

/**
 * Runs all the python tests.
 */
public class JythonTest
{
    private static final String PROTON_TEST_SCRIPT_CLASSPATH_LOCATION = "/proton-test"; // PHTODO rename script??
    private static final Logger LOGGER = Logger.getLogger(JythonTest.class.getName());

    @Test
    public void test() throws Exception
    {
        // PHTODO check whether we still need jproton-test and if so, does it need refactoring?
        // ditto config.sh

        File protonScriptFile = getPythonTestScript();
        String parentDirectory = protonScriptFile.getParent();

        PythonInterpreter interp = new PythonInterpreter();

        LOGGER.info("About to call Jython test script: " + protonScriptFile + " with parent directory: " + parentDirectory + " added to Jython path");

        interp.exec(
        "import sys\n"+
        "sys.path.insert(0,\""+parentDirectory+"\")\n"
        );

        try
        {
            String protonTestPyPath = protonScriptFile.getAbsolutePath();
            interp.execfile(protonTestPyPath);
        }
        catch (PyException e)
        {
            if( e.type.toString().equals("<type 'exceptions.SystemExit'>") && e.value.toString().equals("0") )
            {
                // Build succeeded.
            }
            else
            {
                throw e;
            }
        }
    }


    private File getPythonTestScript() throws URISyntaxException
    {
        URL protonScriptUrl = getClass().getResource(PROTON_TEST_SCRIPT_CLASSPATH_LOCATION);
        File protonScriptFile = new File(protonScriptUrl.toURI());
        return protonScriptFile;
    }

}