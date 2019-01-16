function onUse(player, item, fromPosition, target, toPosition)
	if target:getId() == 3221 and toPosition.x == 31948 and toPosition.y == 31711 and toPosition.z == 06 then 
		item:transform(2859, 1)
		item:decay()
		player:setStorageValue(244, 2)
		Game.sendMagicEffect({x = 31948, y = 31711, z = 06}, 19)
		return true
	end
	return false
end
