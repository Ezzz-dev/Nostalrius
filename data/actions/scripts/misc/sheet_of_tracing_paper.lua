function onUse(player, item, fromPosition, target, toPosition)
	if target:getId() == 2199 and toPosition.x == 32754 and toPosition.y == 32559 and toPosition.z == 09 and player:getStorageValue(315) == 1 then
		item:transform(4843, 1)
		item:decay()
		player:setStorageValue(316, 1)
		target:getPosition():sendMagicEffect(4)
		return true
	end
	return false
end
