local shutdownAtServerSave = true
local cleanMapAtServerSave = false

local function serverSave()
	if shutdownAtServerSave then
		Game.setGameState(GAME_STATE_SHUTDOWN)
	else
		Game.setGameState(GAME_STATE_CLOSED)

		if cleanMapAtServerSave then
			cleanMap()
		end

		Game.setGameState(GAME_STATE_NORMAL)
	end
end

local function secondServerSaveWarning()
	broadcastMessage("Server is saving game in one minute.\nPlease log out.", MESSAGE_STATUS_WARNING)
	addEvent(serverSave, 60000)
end

local function firstServerSaveWarning()
	broadcastMessage("Server is saving game in 3 minutes.\nPlease come back in 10 minutes.", MESSAGE_STATUS_WARNING)
	addEvent(secondServerSaveWarning, 120000)
end

function onTime(interval)
	broadcastMessage("Server is saving game in 5 minutes.\nPlease come back in 10 minutes.", MESSAGE_STATUS_WARNING)
	Game.setGameState(GAME_STATE_STARTUP)
	addEvent(firstServerSaveWarning, 120000)
	return not shutdownAtServerSave
end
