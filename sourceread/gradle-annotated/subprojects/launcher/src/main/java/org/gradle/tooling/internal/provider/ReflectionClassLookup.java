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

package org.gradle.tooling.internal.provider;

import org.gradle.api.Transformer;
import org.gradle.internal.UncheckedException;

import java.io.ObjectStreamClass;
import java.lang.reflect.Method;

public class ReflectionClassLookup implements Transformer<ObjectStreamClass, Class<?>> {
    private final Method lookupMethod;

    public ReflectionClassLookup() {
        try {
            lookupMethod = ObjectStreamClass.class.getDeclaredMethod("lookup", Class.class, Boolean.TYPE);
            lookupMethod.setAccessible(true);
        } catch (NoSuchMethodException e) {
            throw UncheckedException.throwAsUncheckedException(e);
        }
    }

    public ObjectStreamClass transform(Class<?> original) {
        try {
            return (ObjectStreamClass) lookupMethod.invoke(null, original, true);
        } catch (Exception e) {
            throw UncheckedException.throwAsUncheckedException(e);
        }
    }
}
