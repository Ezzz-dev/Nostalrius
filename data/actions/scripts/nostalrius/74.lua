function onUse(player, item, fromPosition, target, toPosition)
	item:getPosition():sendMagicEffect(19)
	player:setStorageValue(259, 0)
	return true
end