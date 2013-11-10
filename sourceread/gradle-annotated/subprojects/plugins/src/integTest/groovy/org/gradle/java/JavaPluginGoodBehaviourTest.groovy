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
package org.gradle.java

import org.gradle.integtests.fixtures.WellBehavedPluginTest
import spock.lang.Issue

class JavaPluginGoodBehaviourTest extends WellBehavedPluginTest {
    @Override
    String getMainTask() {
        return "build"
    }

    @Issue("http://issues.gradle.org/browse/GRADLE-2851")
    def "changing debug flag does not produce deprecation warning"() {
        // We are testing here that Groovy prefers the is*() variant over the get one.
        // If it prefers the get one we'll get a deprecation warning
        given:
        applyPlugin()

        when:
        buildFile << """
            compileJava {
                configure(options) {
                    def value = debug
                    value = failOnError
                }
            }
        """

        then:
        succeeds "tasks"
    }
}