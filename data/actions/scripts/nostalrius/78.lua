function onUse(player, item, fromPosition, target, toPosition)
	if player:getStorageValue(259) == 3 then
		item:getPosition():sendMagicEffect(22)
		player:setStorageValue(259,4)
	else
		item:getPosition():sendMagicEffect(22)
		player:setStorageValue(259,0)
	end
	return true
end