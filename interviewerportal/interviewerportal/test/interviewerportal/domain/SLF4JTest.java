package interviewerportal.domain;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class SLF4JTest {
    private static final Logger LOGGER = LoggerFactory
            .getLogger(SLF4JTest.class);

    public static void main(final String[] args) {

        LOGGER.error("Hello, error");
        LOGGER.warn("Hello, warn");
        LOGGER.info("Hello, info");
        LOGGER.debug("Hello, debug");
        LOGGER.trace("Hello, trace");

        LOGGER.info("{} + {}", 1, 2);

    }
}
