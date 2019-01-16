function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then 
		item:transform(2773, 1)
		item:decay()
		Game.transformItemOnMap({x = 32098, y = 32204, z = 08}, 2772, 2773)
		Game.transformItemOnMap({x = 32100, y = 32205, z = 08}, 622, 1771)
		Game.transformItemOnMap({x = 32101, y = 32205, z = 08}, 622, 1771)
		Game.removeItemOnMap({x = 32100, y = 32205, z = 08}, 4788)
		Game.removeItemOnMap({x = 32101, y = 32205, z = 08}, 4786)
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		Game.transformItemOnMap({x = 32098, y = 32204, z = 08}, 2773, 2772)
		doRelocate({x = 32100, y = 32205, z = 08},{x = 32102, y = 32205, z = 08})
		doRelocate({x = 32101, y = 32205, z = 08},{x = 32102, y = 32205, z = 08})
		Game.transformItemOnMap({x = 32100, y = 32205, z = 08}, 1771, 622)
		Game.transformItemOnMap({x = 32101, y = 32205, z = 08}, 1771, 622)
		Game.createItem(4788, 1, {x = 32100, y = 32205, z = 08})
		Game.createItem(4786, 1, {x = 32101, y = 32205, z = 08})
	end
	return true
end