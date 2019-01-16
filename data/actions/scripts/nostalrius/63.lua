function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then 
		item:transform(2773, 1)
		item:decay()
		Game.transformItemOnMap({x = 32413, y = 32230, z = 10}, 2772, 2773)
		doRelocate({x = 32411, y = 32231, z = 10},{x = 32412, y = 32231, z = 10})
		doRelocate({x = 32410, y = 32231, z = 10},{x = 32412, y = 32231, z = 10})
		doRelocate({x = 32411, y = 32232, z = 10},{x = 32412, y = 32232, z = 10})
		doRelocate({x = 32410, y = 32232, z = 10},{x = 32412, y = 32232, z = 10})
		Game.transformItemOnMap({x = 32410, y = 32231, z = 10}, 1771, 622)
		Game.transformItemOnMap({x = 32411, y = 32231, z = 10}, 1771, 622)
		Game.transformItemOnMap({x = 32411, y = 32232, z = 10}, 1771, 622)
		Game.transformItemOnMap({x = 32410, y = 32232, z = 10}, 1771, 622)
		Game.createItem(4788, 1, {x = 32410, y = 32231, z = 10})
		Game.createItem(4788, 1, {x = 32410, y = 32232, z = 10}) 
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		Game.transformItemOnMap({x = 32413, y = 32230, z = 10}, 2773, 2772)
		Game.transformItemOnMap({x = 32411, y = 32231, z = 10}, 622, 1771)
		Game.transformItemOnMap({x = 32411, y = 32232, z = 10}, 622, 1771)
		Game.transformItemOnMap({x = 32410, y = 32231, z = 10}, 622, 1771)
		Game.transformItemOnMap({x = 32410, y = 32232, z = 10}, 622, 1771)
		Game.removeItemOnMap({x = 32410, y = 32231, z = 10}, 4788)
		Game.removeItemOnMap({x = 32410, y = 32232, z = 10}, 4788)
	end
	
	return true
end