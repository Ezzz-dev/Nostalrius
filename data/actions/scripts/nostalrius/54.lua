function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and Game.isItemThere({x = 32177, y = 32148, z = 11}, 1630) then 
		item:transform(2773, 1)
		item:decay()
		doRelocate({x = 32177, y = 32148, z = 11},{x = 32178, y = 32148, z = 11})
		Game.transformItemOnMap({x = 32177, y = 32148, z = 11}, 1630, 1628)
	elseif item:getId() == 2772 then
		item:transform(2773, 1)
		item:decay()
		Game.transformItemOnMap({x = 32177, y = 32148, z = 11}, 1629, 1628)
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		Game.transformItemOnMap({x = 32177, y = 32148, z = 11}, 1628, 1630)
	end
	return true
end