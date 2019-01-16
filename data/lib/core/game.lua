function Game.sendMagicEffect(position, effect)
	local pos = Position(position)
	pos:sendMagicEffect(effect)
end

function Game.removeItemsOnMap(position)
	local tile = Tile(position)
	local tileCount = tile:getThingCount()
	local i = 0
	while i < tileCount do
		local tileItem = tile:getThing(i)
		if tileItem and tileItem:getType():isMovable() then
			tileItem:remove()
		else
			i = i + 1
		end
	end
end

function Game.transformItemOnMap(position, itemId, toItemId, subtype)
	if not subtype then
		subtype = -1
	end

	local tile = Tile(position)
	local item = tile:getItemById(itemId)
	item:transform(toItemId, subtype)
	item:decay()
	return item
end

function Game.removeItemOnMap(position, itemId, subtype)
	if not subtype then
		subtype = -1
	end
	
	local tile = Tile(position)
	local item = tile:getItemById(itemId, subtype)
	item:remove()
end

function Game.isItemThere(position, itemId)
	local tile = Tile(position)
	return tile:getItemById(itemId) ~= nil
end

function Game.isPlayerThere(position)
	local tile = Tile(position)
	local creatures = tile:getCreatures()
	for _, creature in ipairs(creatures) do
		if creature:isPlayer() then
			return true
		end
	end
	return false
end

function Game.broadcastMessage(message, messageType)
	if messageType == nil then
		messageType = MESSAGE_STATUS_WARNING
	end

	for _, player in ipairs(Game.getPlayers()) do
		player:sendTextMessage(messageType, message)
	end
end

function Game.convertIpToString(ip)
	local band = bit.band
	local rshift = bit.rshift
	return string.format("%d.%d.%d.%d",
		band(ip, 0xFF),
		band(rshift(ip, 8), 0xFF),
		band(rshift(ip, 16), 0xFF),
		rshift(ip, 24)
	)
end

function Game.getReverseDirection(direction)
	if direction == WEST then
		return EAST
	elseif direction == EAST then
		return WEST
	elseif direction == NORTH then
		return SOUTH
	elseif direction == SOUTH then
		return NORTH
	elseif direction == NORTHWEST then
		return SOUTHEAST
	elseif direction == NORTHEAST then
		return SOUTHWEST
	elseif direction == SOUTHWEST then
		return NORTHEAST
	elseif direction == SOUTHEAST then
		return NORTHWEST
	end
	return NORTH
end

function Game.getSkillType(weaponType)
	if weaponType == WEAPON_CLUB then
		return SKILL_CLUB
	elseif weaponType == WEAPON_SWORD then
		return SKILL_SWORD
	elseif weaponType == WEAPON_AXE then
		return SKILL_AXE
	elseif weaponType == WEAPON_DISTANCE then
		return SKILL_DISTANCE
	elseif weaponType == WEAPON_SHIELD then
		return SKILL_SHIELD
	end
	return SKILL_FIST
end

if not globalStorageTable then
	globalStorageTable = {}
end

function Game.getStorageValue(key)
	return globalStorageTable[key]
end

function Game.setStorageValue(key, value)
	globalStorageTable[key] = value
end
