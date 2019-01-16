function onUse(player, item, fromPosition, target, toPosition)
	if player:getStorageValue(259) == 4 then
		item:getPosition():sendMagicEffect(24)
		player:setStorageValue(259,5)
	else
		item:getPosition():sendMagicEffect(24)
		player:setStorageValue(259,0)
	end
	return true
end