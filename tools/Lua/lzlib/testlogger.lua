require("logger")


function test(level)
	print("Set log level to " .. level)
	logger.setLogLevel(level)
	logger.trace("Hello, trace")
	logger.debug("Hello, debug")
	logger.info("Hello, info")
	logger.warning("Hello, warning")
	logger.error("Hello, error")
	print("\n")
end

test(0)
test(1)
test(2)
test(3)
test(4)
test(5)
test(6)