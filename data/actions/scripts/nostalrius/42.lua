function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and Game.isItemThere({x = 32915, y = 32076, z = 06},388) then 
		Game.removeItemOnMap({x = 32915, y = 32076, z = 06}, 388)
		Game.removeItemOnMap({x = 32915, y = 32080, z = 06}, 388)
		item:transform(2773, 1)
		item:decay()
	elseif item:getId() == 2772 then
		item:transform(2773, 1)
		item:decay()
	elseif item:getId() == 2773 and not Game.isItemThere({x = 32915, y = 32076, z = 06}, 388) then 
		doRelocate({x = 32915, y = 32076, z = 06},{x = 32916, y = 32076, z = 06})
		doRelocate({x = 32915, y = 32080, z = 06},{x = 32916, y = 32080, z = 06})
		Game.createItem(388, 1, {x = 32915, y = 32076, z = 06})
		Game.createItem(388, 1, {x = 32915, y = 32080, z = 06})
		item:transform(2772, 1)
		item:decay()
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
	end
	return true
end