/*
 * Copyright 2011 the original author or authors.
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
package org.gradle.api.internal.notations;

import org.gradle.api.artifacts.SelfResolvingDependency;
import org.gradle.api.file.FileCollection;
import org.gradle.api.internal.ClassPathRegistry;
import org.gradle.internal.reflect.Instantiator;
import org.gradle.api.internal.artifacts.dependencies.DefaultSelfResolvingDependency;
import org.gradle.api.internal.artifacts.dsl.dependencies.DependencyFactory;
import org.gradle.api.internal.file.FileResolver;
import org.gradle.api.internal.notations.api.NotationParser;
import org.gradle.api.internal.notations.parsers.TypedNotationParser;

import java.io.File;
import java.util.Collection;

public class DependencyClassPathNotationParser
        extends TypedNotationParser<DependencyFactory.ClassPathNotation, SelfResolvingDependency>
        implements NotationParser<SelfResolvingDependency> {

    private final ClassPathRegistry classPathRegistry;
    private final Instantiator instantiator;
    private final FileResolver fileResolver;

    public DependencyClassPathNotationParser(Instantiator instantiator, ClassPathRegistry classPathRegistry,
                                             FileResolver fileResolver) {
        super(DependencyFactory.ClassPathNotation.class);

        this.instantiator = instantiator;
        this.classPathRegistry = classPathRegistry;
        this.fileResolver = fileResolver;
    }

    @Override
    public void describe(Collection<String> candidateFormats) {
        candidateFormats.add("ClassPathNotation, e.g. gradleApi().");
    }

    public SelfResolvingDependency parseType(DependencyFactory.ClassPathNotation notation) {
        Collection<File> classpath = classPathRegistry.getClassPath(notation.name()).getAsFiles();
        FileCollection files = fileResolver.resolveFiles(classpath);
        return instantiator.newInstance(DefaultSelfResolvingDependency.class, files);
    }
}
