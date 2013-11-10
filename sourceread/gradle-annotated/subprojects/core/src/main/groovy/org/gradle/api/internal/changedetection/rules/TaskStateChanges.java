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

package org.gradle.api.internal.changedetection.rules;

public interface TaskStateChanges extends Iterable<TaskStateChange> {
    /**
     * Snapshot any final state after the task has executed. This method is executed only if the task is to be executed.
     * Any persistent state should be added to the {@link org.gradle.api.internal.changedetection.state.TaskExecution} object for the current execution.
     */
    void snapshotAfterTask();
}
