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
package org.gradle.initialization;

/**
 * An object that performs some action with a {@link BuildController} and produces a “result” object (e.g. the output).
 * <p>
 * Implementations of this are typically composed to bootstrap a build in a certain environment.
 * <p>
 */
public interface BuildAction<T> {
    /**
     * Executes the action with the given controller.
     * <p>
     * The state of the build is not defined as part of this contract, it is highly context specific.
     */
    T run(BuildController buildController);
}
