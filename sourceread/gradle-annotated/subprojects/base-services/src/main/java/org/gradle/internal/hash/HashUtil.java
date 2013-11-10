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
package org.gradle.internal.hash;

import org.gradle.api.UncheckedIOException;
import org.gradle.internal.UncheckedException;

import java.io.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class HashUtil {
    public static HashValue createHash(String scriptText, String algorithm) {
        MessageDigest messageDigest = createMessageDigest(algorithm);
        messageDigest.update(scriptText.getBytes());
        return new HashValue(messageDigest.digest());
    }

    public static HashValue createHash(File file, String algorithm) {
        try {
            return createHash(new FileInputStream(file), algorithm);
        } catch (FileNotFoundException e) {
            throw new UncheckedIOException(e);
        }
    }

    public static HashValue createHash(InputStream instr, String algorithm) {
        MessageDigest messageDigest = createMessageDigest(algorithm);
        try {
            byte[] buffer = new byte[4096];
            try {
                while (true) {
                    int nread = instr.read(buffer);
                    if (nread < 0) {
                        break;
                    }
                    messageDigest.update(buffer, 0, nread);
                }
            } finally {
                instr.close();
            }
        } catch (IOException e) {
            throw new UncheckedIOException(e);
        }
        return new HashValue(messageDigest.digest());
    }

    private static MessageDigest createMessageDigest(String algorithm) {
        try {
            return MessageDigest.getInstance(algorithm);
        } catch (NoSuchAlgorithmException e) {
            throw UncheckedException.throwAsUncheckedException(e);
        }
    }

    public static String createCompactMD5(String scriptText) {
        return createHash(scriptText, "MD5").asCompactString();
    }

    public static HashValue sha1(byte[] bytes) {
        return createHash(new ByteArrayInputStream(bytes), "SHA1");
    }

    public static HashValue sha1(InputStream inputStream) {
        return createHash(inputStream, "SHA1");
    }

    public static HashValue sha1(File file) {
        return createHash(file, "SHA1");
    }
}
