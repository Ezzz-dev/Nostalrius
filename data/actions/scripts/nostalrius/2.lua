function onUse(player, item, fromPosition, target, toPosition)
	if Game.isItemThere({x = 33211, y = 32698, z = 13}, 1306) then
		Game.removeItemOnMap({x = 33211, y = 32698, z = 13}, 1306)
	else
		doRelocate({x = 33211, y = 32698, z = 13}, {x = 33211, y = 32697, z = 13})
		Game.createItem(1306, 1, {x = 33211, y = 32698, z = 13})
	end
	return true
end