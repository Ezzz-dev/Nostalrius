function onStepIn(creature, item, position, fromPosition)
	if not Game.isItemThere({x = 32266, y = 31861, z = 11}, 2772) then
		Game.transformItemOnMap({x = 32266, y = 31861, z = 11}, 2773, 2772)
		Game.transformItemOnMap({x = 32266, y = 31860, z = 11}, 411, 410)
		Game.createItem(2129, 1, {x = 32266, y = 31860, z = 11})
	end
end

function onAddItem(item, tileitem, position)
	if not Game.isItemThere({x = 32266, y = 31861, z = 11}, 2772) then
		Game.transformItemOnMap({x = 32266, y = 31861, z = 11}, 2773, 2772)
		Game.transformItemOnMap({x = 32266, y = 31860, z = 11}, 411, 410)
		Game.createItem(2129, 1, {x = 32266, y = 31860, z = 11})
	end
end