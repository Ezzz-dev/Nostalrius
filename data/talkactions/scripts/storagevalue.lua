function onSay(player, words, param)
	if not player:getGroup():getAccess() then
		return true
	end
	
	local split = param:split(",")
	if split[2] == nil then
		player:sendCancelMessage("Insufficient parameters.")
		return false
	end
	
	player:setStorageValue(tonumber(split[1]), tonumber(split[2]))
	player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "[Storage Value] " .. split[1] .. " changed it's value to " .. split[2] .. ".")
	return false
end
