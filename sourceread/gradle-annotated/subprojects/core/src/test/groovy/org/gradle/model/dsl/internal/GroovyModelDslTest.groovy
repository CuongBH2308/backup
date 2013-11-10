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

package org.gradle.model.dsl.internal

import org.gradle.model.internal.DefaultModelRegistry
import org.gradle.model.internal.ModelRegistryBackedModelRules
import spock.lang.Specification

class GroovyModelDslTest extends Specification {

    def modelRegistry = new DefaultModelRegistry()
    def modelRules = new ModelRegistryBackedModelRules(modelRegistry)
    def modelDsl = new GroovyModelDsl(modelRules)

    def "can add rules via dsl"() {
        given:
        modelRules.register("foo.bar", [])

        when:
        modelDsl.foo.bar {
            add 1
        }

        then:
        modelRegistry.get("foo.bar", List) == [1]

    }

}
