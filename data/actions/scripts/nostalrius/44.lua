function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then 
		Game.removeItemOnMap({x = 32649, y = 32923, z = 08}, 1822)
		Game.transformItemOnMap({x = 32649, y = 32923, z = 08}, 351, 385)
		Game.transformItemOnMap({x = 32652, y = 32922, z = 08}, 2772, 2773)
	elseif item:getId() == 2773 then 
		Game.transformItemOnMap({x = 32649, y = 32923, z = 08}, 385, 351)
		Game.createItem(1822, 1, {x = 32649, y = 32923, z = 08})
		Game.transformItemOnMap({x = 32652, y = 32922, z = 08}, 2773, 2772)
	end
	return true
end