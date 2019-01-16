function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then 
		item:transform(2773, 1)
		item:decay()
		doRelocate({x = 32426, y = 32202, z = 14},{x = 32426, y = 32200, z = 14})
		doRelocate({x = 32426, y = 32201, z = 14},{x = 32426, y = 32200, z = 14})
		doRelocate({x = 32427, y = 32202, z = 14},{x = 32427, y = 32200, z = 14})
		doRelocate({x = 32427, y = 32201, z = 14},{x = 32427, y = 32200, z = 14})
		Game.removeItemOnMap({x = 32426, y = 32202, z = 14}, 1771)
		Game.removeItemOnMap({x = 32426, y = 32201, z = 14}, 1771)
		Game.removeItemOnMap({x = 32427, y = 32202, z = 14}, 1771)
		Game.removeItemOnMap({x = 32427, y = 32201, z = 14}, 1771)
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		Game.createTile({x = 32426, y = 32201, z = 14}, true)
		Game.createTile({x = 32427, y = 32201, z = 14}, true)
		Game.createTile({x = 32426, y = 32202, z = 14}, true)
		Game.createTile({x = 32427, y = 32202, z = 14}, true)
		Game.createItem(1771, 1, {x = 32426, y = 32201, z = 14})
		Game.createItem(1771, 1, {x = 32427, y = 32201, z = 14})
		Game.createItem(1771, 1, {x = 32426, y = 32202, z = 14})
		Game.createItem(1771, 1, {x = 32427, y = 32202, z = 14})
	end
	return true
end