function onUse(player, item, fromPosition, target, toPosition)
	item:getPosition():sendMagicEffect(3)
	item:remove()
	return true
end
