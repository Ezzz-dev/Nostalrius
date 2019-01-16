function onSay(player, words, param)
	if not getPlayerFlagValue(player, PlayerFlag_CanBroadcast) then
		return true
	end

	print("> " .. player:getName() .. " broadcasted: \"" .. param .. "\".")
	for _, targetPlayer in ipairs(Game.getPlayers()) do
		targetPlayer:sendTextMessage(MESSAGE_STATUS_WARNING, param)
	end
	return false
end
