function onUse(player, item, fromPosition, target, toPosition)
	item:transform(3481, 1)
	item:decay()
	item:getPosition():sendMagicEffect(3)
	return true
end
