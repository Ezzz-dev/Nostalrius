function onUse(player, item, fromPosition, target, toPosition)
	if player:getStorageValue(259) == 2 then
		item:getPosition():sendMagicEffect(25)
		player:setStorageValue(259,3)
	else
		item:getPosition():sendMagicEffect(25)
		player:setStorageValue(259,0)
	end
	return true
end