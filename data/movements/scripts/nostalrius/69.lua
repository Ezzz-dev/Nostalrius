function onAddItem(item, tileitem, position)
	if Game.isItemThere({x = 33135, y = 32682, z = 12},3042) then 
		doRelocate({x = 33135, y = 32683, z = 12},{x = 33130, y = 32683, z = 12})
		Game.sendMagicEffect({x = 33135, y = 32683, z = 12}, 11)
		Game.sendMagicEffect({x = 33130, y = 32683, z = 12}, 11)
		Game.sendMagicEffect({x = 33135, y = 32682, z = 12}, 16)
		Game.removeItemOnMap({x = 33135, y = 32682, z = 12}, 3042)
	else
		Game.sendMagicEffect({x = 33135, y = 32682, z = 12}, 3)
	end
end
