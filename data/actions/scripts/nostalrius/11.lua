function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2773 and Game.isItemThere({x = 32685, y = 32084, z = 09}, 1771) then 
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 32687, y = 32084, z = 09},{x = 32683, y = 32084, z = 09})
		doRelocate({x = 32686, y = 32084, z = 09},{x = 32683, y = 32084, z = 09})
		doRelocate({x = 32685, y = 32084, z = 09},{x = 32683, y = 32084, z = 09})
		doRelocate({x = 32684, y = 32084, z = 09},{x = 32683, y = 32084, z = 09})
		Game.transformItemOnMap({x = 32687, y = 32084, z = 09}, 1771, 727)
		Game.createItem(4798, 1, {x = 32687, y = 32084, z = 09})
		Game.transformItemOnMap({x = 32686, y = 32084, z = 09}, 1771, 727)
		Game.transformItemOnMap({x = 32685, y = 32084, z = 09}, 1771, 727)
		Game.transformItemOnMap({x = 32684, y = 32084, z = 09}, 1771, 727)
		Game.createItem(4800, 1, {x = 32684, y = 32084, z = 09})
	elseif item:getId() == 2773 then
		item:transform(2772, 1)
		item:decay()
	elseif item:getId() == 2772 and Game.isItemThere({x = 32685, y = 32084, z = 09},727) then
		item:transform(2773, 1)
		item:decay()
		Game.removeItemOnMap({x = 32684, y = 32084, z = 09}, 4800)
		Game.transformItemOnMap({x = 32684, y = 32084, z = 09}, 727, 1771)
		Game.transformItemOnMap({x = 32685, y = 32084, z = 09}, 727, 1771)
		Game.removeItemOnMap({x = 32687, y = 32084, z = 09}, 4798)
		Game.transformItemOnMap({x = 32687, y = 32084, z = 09}, 727, 1771)
		Game.transformItemOnMap({x = 32686, y = 32084, z = 09}, 727, 1771)
	elseif item:getId() == 2772 then
		item:transform(2773, 1)
		item:decay()
	end
	return true
end