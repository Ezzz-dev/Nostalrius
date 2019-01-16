function onUse(player, item, fromPosition, target, toPosition)
	if player:getStorageValue(259) == 0 then
		item:getPosition():sendMagicEffect(23)
		player:setStorageValue(259, 1)
	else
		item:getPosition():sendMagicEffect(23)
		player:setStorageValue(259, 0)
	end
	return true
end