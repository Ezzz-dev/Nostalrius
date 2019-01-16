function onUse(player, item, fromPosition, target, toPosition)
	if player:getStorageValue(259) == 1 then
		item:getPosition():sendMagicEffect(20)
		player:setStorageValue(259,2)
	else
		item:getPosition():sendMagicEffect(20)
		player:setStorageValue(259,0)
	end
	return true
end