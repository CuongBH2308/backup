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

package org.gradle.internal.service

import org.gradle.test.fixtures.concurrent.ConcurrentSpec
import org.gradle.internal.Factory

class DefaultServiceRegistryConcurrencyTest extends ConcurrentSpec {
    def "multiple threads can locate services"() {
        def registry = new DefaultServiceRegistry()
        registry.addProvider(new Object() {
            String createString(Integer value) {
                return value.toString()
            }

            Integer createInteger() {
                return 12
            }

            Long createLong(BigDecimal value) {
                return value.longValue()
            }

            BigDecimal createBigDecimal() {
                return 123
            }
        })

        expect:
        10.times {
            start {
                assert registry.get(String) == "12"
                assert registry.get(Long) == 123
            }
        }
    }

    def "multiple threads can locate factories"() {
        def registry = new DefaultServiceRegistry()
        registry.addProvider(new Object() {
            Factory<String> createString(BigDecimal value) {
                return { value.toString() } as Factory
            }

            Factory<Integer> createInteger(Long value) {
                return { 12 } as Factory
            }

            Long createLong() {
                return 2L
            }

            BigDecimal createBigDecimal() {
                return 123
            }
        })

        expect:
        10.times {
            start {
                assert registry.getFactory(Integer).create() == 12
                assert registry.getFactory(String).create() == "123"
            }
        }
    }

    def "multiple threads can locate all services"() {
        def registry = new DefaultServiceRegistry()
        registry.addProvider(new Object() {
            String createString(Integer value) {
                return value.toString()
            }

            Integer createInteger() {
                return 12
            }

            String createOther(BigDecimal value) {
                return value.toString()
            }

            BigDecimal createBigDecimal() {
                return 123
            }
        })

        expect:
        10.times {
            start {
                assert registry.getAll(Number).sort() == [12, 123]
                assert registry.getAll(String).sort() == ["12", "123"]
            }
        }
    }

    def "close blocks while other threads are locating services"() {
        def registry = new DefaultServiceRegistry()
        registry.addProvider(new Object() {
            String createString() {
                DefaultServiceRegistryConcurrencyTest.this.instant.constructing
                DefaultServiceRegistryConcurrencyTest.this.thread.block()
                DefaultServiceRegistryConcurrencyTest.this.instant.constructed
                "hi"
            }
        })

        when:
        start {
            assert registry.get(String) == "hi"
        }
        async {
            thread.blockUntil.constructing
            registry.close()
            instant.stopped
        }

        then:
        instant.constructed < instant.stopped
    }
}
