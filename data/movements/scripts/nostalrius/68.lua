function onAddItem(item, tileitem, position)
	if Game.isItemThere({x = 33161, y = 32831, z = 10},3042) then 
		doRelocate({x = 33162, y = 32831, z = 10},{x = 33158, y = 32832, z = 10})
		Game.sendMagicEffect({x = 33162, y = 32831, z = 10}, 11)
		Game.sendMagicEffect({x = 33158, y = 32832, z = 10}, 11)
		Game.sendMagicEffect({x = 33161, y = 32831, z = 10}, 16)
		Game.removeItemOnMap({x = 33161, y = 32831, z = 10}, 3042)
	else
		Game.sendMagicEffect({x = 33161, y = 32831, z = 10}, 3)
	end
end
