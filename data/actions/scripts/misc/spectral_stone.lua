function onUse(player, item, fromPosition, target, toPosition)
	if target:getId() == 599 and toPosition.x == 32665 and toPosition.y == 32736 and toPosition.z == 06 and player:getStorageValue(320) == 5 then
		player:setStorageValue(321,1)
		target:getPosition():sendMagicEffect(13)
		return true
	elseif target:getId() == 599 and toPosition.x == 32497 and toPosition.y == 31622 and toPosition.z == 06 and player:getStorageValue(320) == 5 then
		player:setStorageValue(322,1)
		target:getPosition():sendMagicEffect(13)
		return true
	end
	return false
end
