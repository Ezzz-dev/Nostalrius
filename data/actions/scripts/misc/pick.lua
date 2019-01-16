function onUse(player, item, fromPosition, target, toPosition)
	local tile = Tile(toPosition)
	if not tile then
		return false
	end

	local ground = tile:getGround()
	if not ground then
		return false
	end
	
	if ground:getId() == 372 then
		ground:transform(394, 1)
		ground:decay()
		return true
	elseif target:getId() == 1772 and toPosition.x == 32648 and toPosition.y == 32134 and toPosition.z == 10 and math.random(1, 100) <= 40 then 
		Game.sendMagicEffect({x = 32648, y = 32134, z = 10}, 3)
		Game.removeItemOnMap({x = 32648, y = 32134, z = 10}, 1772)
		return true
	elseif target:getId() == 1772 and toPosition.x == 32648 and toPosition.y == 32134 and toPosition.z == 10 then 
		Game.sendMagicEffect({x = 32648, y = 32134, z = 10}, 3)
		doTargetCombatHealth(0, player, COMBAT_PHYSICALDAMAGE, -40, -40)
		return true
	elseif target:getId() == 1791 and toPosition.x == 32356 and toPosition.y == 32074 and toPosition.z == 10 and math.random(1, 100) <= 40 then 
		Game.sendMagicEffect({x = 32356, y = 32074, z = 10}, 3)
		Game.removeItemOnMap({x = 32356, y = 32074, z = 10}, 1791)
		return true
	elseif target:getId() == 1791 and toPosition.x == 32356 and toPosition.y == 32074 and toPosition.z == 10 then
		Game.sendMagicEffect({x = 32356, y = 32074, z = 10}, 3)
		doTargetCombatHealth(0, player, COMBAT_PHYSICALDAMAGE, -50, -50)
		return true
	end
	return false
end
