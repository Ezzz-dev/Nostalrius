function onSay(player, words, param)
	if not player:getGroup():getAccess() then
		return true
	end

	local split = param:split(",")
	local position = {x = split[1], y = split[2], z = split[3]}
	return player:teleportTo(position)
end
