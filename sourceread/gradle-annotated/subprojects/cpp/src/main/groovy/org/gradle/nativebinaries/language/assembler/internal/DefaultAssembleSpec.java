/*
 * Copyright 2013 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.gradle.nativebinaries.language.assembler.internal;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class DefaultAssembleSpec implements AssembleSpec {

    private List<File> source = new ArrayList<File>();
    private List<String> args = new ArrayList<String>();
    private File objectFileDir;
    private File tempDir;

    public List<File> getSourceFiles() {
        return source;
    }

    public void source(Iterable<File> sources) {
        for (File file : sources) {
            this.source.add(file);
        }
    }

    public File getObjectFileDir() {
        return objectFileDir;
    }

    public void setObjectFileDir(File objectFileDir) {
        this.objectFileDir = objectFileDir;
    }

    public File getTempDir() {
        return tempDir;
    }

    public void setTempDir(File tempDir) {
        this.tempDir = tempDir;
    }

    public List<String> getArgs() {
        return args;
    }

    public void args(List<String> args) {
        this.args.addAll(args);
    }

}
