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
package org.gradle.api.plugins;

/**
 * Objects that can be extended at runtime with other objects.
 *
 * <pre autoTested="">
 * // Extensions are just plain objects, there is no interface/type
 * class MyExtension {
 *   String foo
 *
 *   MyExtension(String foo) {
 *     this.foo = foo
 *   }
 * }
 *
 * // Add new extensions via the extension container
 * project.extensions.create('custom', MyExtension, "bar")
 * //                       («name»,   «type»,       «constructor args», …)
 *
 * // extensions appear as properties on the target object by the given name
 * assert project.custom instanceof MyExtension
 * assert project.custom.foo == "bar"
 *
 * // also via a namespace method
 * project.custom {
 *   assert foo == "bar"
 *   foo = "other"
 * }
 * assert project.custom.foo == "other"
 *
 * // Extensions added with the extension container's create method are themselves extensible
 * assert project.custom instanceof ExtensionAware
 * project.custom.extensions.create("nested", MyExtension, "baz")
 * assert project.custom.nested.foo == "baz"
 *
 * // All extension aware objects have a special “ext” extension of type ExtraPropertiesExtension
 * assert project.hasProperty("myProperty") == false
 * project.ext.myProperty = "myValue"
 *
 * // Properties added to the “ext” extension are promoted to the owning object
 * assert project.myProperty == "myValue"
 * </pre>
 *
 * Many Gradle objects are extension aware. This includes; projects, tasks, configurations, dependencies etc.
 * <p>
 * For more on adding & creating extensions, see {@link ExtensionContainer}.
 * <p>
 * For more on extra properties, see {@link ExtraPropertiesExtension}.
 */
public interface ExtensionAware {

    /**
     * The container of extensions.
     */
    ExtensionContainer getExtensions();

}
