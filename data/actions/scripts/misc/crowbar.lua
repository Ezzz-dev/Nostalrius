function onUse(player, item, fromPosition, target, toPosition)
	if not target:isItem() then
		return false
	end
	
	if target:getId() == 4848 and player:getStorageValue(297) == 0 then 
		player:setStorageValue(297, 1)
		target:getPosition():sendMagicEffect(1)
		target:transform(4849, 1)
		target:decay()
		return true
	elseif target:getId() == 4848 and player:getStorageValue(297) == 1 then 
		player:setStorageValue(297, 2)
		target:getPosition():sendMagicEffect(1)
		target:transform(4849, 1)
		target:decay()
		return true
	elseif target:getId() == 4848 and player:getStorageValue(297) == 2 then 
		player:setStorageValue(297, 3)
		target:getPosition():sendMagicEffect(1)
		target:transform(4849, 3)
		target:decay()
		return true
	elseif target:getId() == 1628 and toPosition.x == 32680 and toPosition.y == 32083 and toPosition.z == 09 then 
		Game.transformItemOnMap({x = 32680, y = 32083, z = 09}, 1628, 1630)
		return true
	elseif target:getId() == 3501 and toPosition.x == 32013 and toPosition.y == 31562 and toPosition.z == 04 and player:getStorageValue(228) == 1 then
		Game.sendMagicEffect({x = 32013, y = 31562, z = 04}, 15)
		player:setStorageValue(228, 2)
		return true
	elseif target:getId() == 3501 and toPosition.x == 32013 and toPosition.y == 31562 and toPosition.z == 04 then
		Game.sendMagicEffect({x = 32013, y = 31562, z = 04}, 3)
		return true
	end
	return doDestroyItem(target)
end
