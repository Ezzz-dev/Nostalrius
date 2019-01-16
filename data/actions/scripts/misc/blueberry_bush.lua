function onUse(player, item, fromPosition, target, toPosition)
	item:transform(3700, 1)
	item:decay()
	Game.createItem(3588, 3, fromPosition)
	return true
end
