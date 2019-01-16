function onSay(player, words, param)
	if not player:getGroup():getAccess() then
		return true
	end

	local position = player:getPosition()
	position.z = position.z + 1
	
	local tile = Tile(position)
	if tile == nil or tile:getGround() == nil then
		player:sendCancelMessage("You cannot teleport there.")
		return false
	end
	
	player:teleportTo(position)
	return false
end
