-- log utility

-- Reference: full fledged libraries:
-- lualogging: http://www.keplerproject.org/lualogging/
-- log4lua: http://code.google.com/p/log4lua/

logger = {}

local LEVEL_LABEL = { "ERROR", "WARNING", "INFO", "DEBUG", "TRACE" }
-- error = 1
-- warning = 2
-- info = 3
-- debug = 4
-- trace = 5

loglevel = 3

function logger.setLogLevel(level)
	loglevel = level
end

-- FIXME: how to print the right file and line
local function prependMsg(level, msg)
	local label = LEVEL_LABEL[level]
	local datetime = os.date()
	local source = debug.getinfo(1).source
	local line = debug.getinfo(1).currentline
	return datetime .. "-" .. label .. ": " .. source .. "(" .. line .. ")" .. ": " .. msg
end



local function logmsg(level, msg)
	if loglevel >= level then
		print(prependMsg(level, msg))
	end
end

function logger.error(msg)
	logmsg(1, msg)
end

function logger.warning(msg)
	logmsg(2, msg)
end

function logger.info(msg)
	logmsg(3, msg)
end

function logger.debug(msg)
	logmsg(4, msg)
end

function logger.trace(msg)
	logmsg(5, msg)
end