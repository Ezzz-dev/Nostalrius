function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and Game.isItemThere({x = 33295, y = 31677, z = 15},1791) then
		item:transform(2773, 1)
		item:decay()
		Game.removeItemOnMap({x = 33295, y = 31677, z = 15}, 1791)
		Game.removeItemOnMap({x = 33296, y = 31677, z = 15}, 1791)
		Game.removeItemOnMap({x = 33297, y = 31677, z = 15}, 1791)
		Game.removeItemOnMap({x = 33298, y = 31677, z = 15}, 1791)
		Game.removeItemOnMap({x = 33299, y = 31677, z = 15}, 1791)
	elseif item:getId() == 2772 then 
		item:transform(2773, 1)
		item:decay()
	elseif item:getId() == 2773 and Game.isItemThere({x = 33295, y = 31677, z = 15}, 1791) then
		item:transform(2772, 1)
		item:decay()
	elseif item:getId() == 2773 then
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 33295, y = 31677, z = 15},{x = 33295, y = 31678, z = 15})
		doRelocate({x = 33296, y = 31677, z = 15},{x = 33296, y = 31678, z = 15})
		doRelocate({x = 33297, y = 31677, z = 15},{x = 33297, y = 31678, z = 15})
		doRelocate({x = 33298, y = 31677, z = 15},{x = 33298, y = 31678, z = 15})
		doRelocate({x = 33299, y = 31677, z = 15},{x = 33299, y = 31678, z = 15})
		Game.createItem(1791, 1, {x = 33295, y = 31677, z = 15})
		Game.createItem(1791, 1, {x = 33296, y = 31677, z = 15})
		Game.createItem(1791, 1, {x = 33297, y = 31677, z = 15})
		Game.createItem(1791, 1, {x = 33298, y = 31677, z = 15})
		Game.createItem(1791, 1, {x = 33299, y = 31677, z = 15})
	end
	return true
end