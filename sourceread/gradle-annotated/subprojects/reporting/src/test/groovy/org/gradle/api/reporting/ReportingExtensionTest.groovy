/*
 * Copyright 2009 the original author or authors.
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

package org.gradle.api.reporting

import spock.lang.Specification
import org.gradle.testfixtures.ProjectBuilder
import org.gradle.api.Project

class ReportingExtensionTest extends Specification {
    
    Project project = ProjectBuilder.builder().build()
    ReportingExtension extension = new ReportingExtension(project)
    
    def "defaults to reports dir in build dir"() {
        expect:
        extension.baseDir == new File(project.buildDir, ReportingExtension.DEFAULT_REPORTS_DIR_NAME)

        when:
        project.buildDir = project.file("newBuildDir")

        then:
        extension.baseDir == new File(project.buildDir, ReportingExtension.DEFAULT_REPORTS_DIR_NAME)
    }
    
    def "reports dir can be changed lazily"() {
        given:
        def dir = "a"

        when:
        extension.baseDir = { dir }

        then:
        extension.baseDir == project.file("a")

        when:
        dir = "b"

        then:
        extension.baseDir == project.file("b")

    }
}
